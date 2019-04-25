/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Created by lucasg,
*/

#include <Abstractions/Mutex.hpp>
#include "Reception.hpp"
#include "PlazzaServerAPIManager.hpp"

static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

static bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
            s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

static std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;

    while (getline(ss, item, delim)) {
        ltrim(item);
        rtrim(item);
        result.push_back(item);
    }
    return result;
}

plaz::Reception::Reception(const std::string &multiplier, const std::string &cooks, const std::string &kitchen)
    : _logFile("plazza-log.txt", std::ios_base::app)
{
    this->_multiplier = std::stoi(multiplier);
    this->_cooksNumber = std::stoi(cooks);
    this->_kitchenStockTimeout = std::stoi(kitchen);
    //this->_mutex = new plaz::abs::Mutex();
    this->_timeoutThread = new plaz::abs::Thread<void>([this]() {
        plaz::abs::DataQueue<> queue("/plazzaTimeout", plaz::abs::DataQueue<>::Mode::Read, true);
        while (true) {
            auto id = queue.pull();

            for (auto &[kitchen, process] : this->_kitchens) {
                (void)process;
                if (kitchen->getKitchenId() == std::atoi(id.c_str())) {
                    std::cout << "Kitchen " << id << " just closed" << std::endl;
                    this->_kitchens.erase(kitchen);
                    break;
                }
            }
        }
    });
    this->_logThread = new plaz::abs::Thread<void>([this]() {
        plaz::abs::DataQueue<> queue("/plazzaLog", plaz::abs::DataQueue<>::Mode::Read, true);

        while (true) {
            auto msg = queue.pull();

            std::cout << msg << std::endl;
            this->_logFile << msg + "\n";
        }
    });
}

void plaz::Reception::receiveOrders() {
    std::vector<Order> orders;

    for (std::string line; std::getline(std::cin, line);) {
        auto vector = split(line, ';');

        if (line == "status") {
            this->status();
            continue;
        }
        if (line == "exit") {
            this->quit();
            break;
        }
        for (const auto &order : vector) {
            orders.emplace_back(order);
        }
        this->sendOrders(orders);
        orders.clear();
    }
}

void plaz::Reception::serverModeReception() {
    for (std::string line; std::getline(std::cin, line);) {
        if (line == "exit")
            break;
    }
    this->quit();
}

void plaz::Reception::sendOrders(std::vector<plaz::Order> orders) {
    for (auto &order : orders) {
        for (int i = 0; i < order.getAmount(); i++) {
            if (!order.isValid())
                continue;
            auto sended = order.getPizza().pack();
            auto kitchen = getAvailableKitchen(order.getPizza());
            (*kitchen->getData())->waitingPizza = sended;
            while ((*kitchen->getData())->waitingPizza != -1);
        }
    }
}

plaz::AKitchen *plaz::Reception::getAvailableKitchen(plaz::Pizza pizza) {
    for (auto &[kitchen, process] : this->_kitchens) {
        (void)process;
        if ((*kitchen->getData())->availableSlots <= 0
            || (*kitchen->getData())->waitingPizza != -1)
            continue;
        if (pizza.checkCanConsumePizza(kitchen->getData())) {
            return kitchen;
        }
    }
    return this->initNewKitchen();
}

plaz::AKitchen *plaz::Reception::initNewKitchen() {
    auto *kitchen = new plaz::AKitchen(this->_kitchens.size() + 1, this->_cooksNumber, this->_kitchenStockTimeout, this->_multiplier);
    auto *process = new plaz::abs::Process();
    std::vector<std::string_view> args{std::to_string(kitchen->getKitchenId()), std::to_string(this->_cooksNumber),
                                       std::to_string(this->_kitchenStockTimeout), std::to_string(this->_multiplier)};
    std::vector<std::string_view> env;

    kitchen->initKitchen();
    this->_kitchens.emplace(kitchen, process);
    process->exec(std::string_view("./kitchen"), args, env);
    return (kitchen);
}

int plaz::Reception::getMultiplier() {
    return this->_multiplier;
}

int plaz::Reception::getMaxCooksNumber() {
    return this->_cooksNumber;
}

int plaz::Reception::getKitchenStockTimeout() {
    return this->_kitchenStockTimeout;
}

void plaz::Reception::status() {
    for (auto &[kitchen, process] : this->_kitchens) {
        (void) process;
        auto str = std::string("---- Kitchen " + std::to_string(kitchen->getKitchenId()) + "----");

        std::cout << str << std::endl;
        std::cout << "Stock:" << std::endl;
        std::cout << "\tDoe:" << (*kitchen->getData())->stockDoe << std::endl;
        std::cout << "\tTomatoe:" << (*kitchen->getData())->stockTomato << std::endl;
        std::cout << "\tGruyere:" << (*kitchen->getData())->stockGruyere << std::endl;
        std::cout << "\tHam:" << (*kitchen->getData())->stockHam << std::endl;
        std::cout << "\tMushrooms:" << (*kitchen->getData())->stockMushrooms << std::endl;
        std::cout << "\tSteak:" << (*kitchen->getData())->stockSteak << std::endl;
        std::cout << "\tEggPlant:" << (*kitchen->getData())->stockEggPlant << std::endl;
        std::cout << "\tGoatCheese:" << (*kitchen->getData())->stockGoatCheese << std::endl;
        std::cout << "\tChiefLove:" << (*kitchen->getData())->stockChiefLove << std::endl;
        std::cout << "Free chiefs: " << (*kitchen->getData())->availableSlots << " / " << this->_cooksNumber << std::endl;
        std::cout << std::string(str.length(), '-') << std::endl;
    }
}

void plaz::Reception::quit() {
    for (auto &[kitchen, process] : this->_kitchens) {
        (void) kitchen;
        process->kill();
    }
    this->_logFile.close();
}

std::vector<plaz::AKitchen *> plaz::Reception::getRunningKitchens() const {
    std::vector<plaz::AKitchen *> runningKitchens;

    for (auto &[kitchen, process] : this->_kitchens) {
        (void) process;
        runningKitchens.push_back(kitchen);
    }
    return runningKitchens;
}

void plaz::Reception::setServerMode() {
    this->serverMode = true;
}

bool plaz::Reception::isServerMode() {
    return this->serverMode;
}