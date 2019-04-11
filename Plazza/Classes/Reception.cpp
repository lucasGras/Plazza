/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Created by lucasg,
*/
#include "Reception.hpp"
#include <thread>

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

plaz::Reception::Reception(const std::string &multiplier, const std::string &cooks, const std::string &kitchen) {
    this->_multiplier = std::stoi(multiplier);
    this->_cooksNumber = std::stoi(cooks);
    this->_kitchenStockTimeout = std::stoi(kitchen);
}

void plaz::Reception::receiveOrders() {
    std::vector<Order> orders;

    for (std::string line; std::getline(std::cin, line);) {
        auto vector = split(line, ';');

        if (line == "status") {
            this->status();
            continue;
        }
        if (line == "exit")
            this->quit();
        for (const auto &order : vector) {
            orders.emplace_back(order);
        }
        this->sendOrders(orders);
        orders.clear();
    }
}

void plaz::Reception::sendOrders(std::vector<plaz::Order> orders) {
    for (auto &order : orders) {
        for (int i = 0; i < order.getAmount(); i++) {
            if (!order.isValid())
                continue;
            auto sended = order.getPizza().pack();
            auto kitchen = getAvailableKitchen(order.getPizza());
            std::cout << "[RECEPTION] Send pizza in kitchen (" << kitchen->getKitchenId() << ")" << std::endl;
            (*kitchen->getData())->waitingPizza = sended;
            while ((*kitchen->getData())->waitingPizza != -1);
        }
    }
}

plaz::AKitchen *plaz::Reception::getAvailableKitchen(plaz::Pizza pizza) {
    for (auto &[kitchen, process] : this->_kitchens) {
        (void)process;
        if ((*kitchen->getData())->waitingPizza != -1)
            continue;
        if ((*kitchen->getData())->availableCooks <= 0)
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
    std::vector<std::string_view> args{std::to_string(kitchen->getKitchenId()), std::to_string(this->_cooksNumber), std::to_string(this->_kitchenStockTimeout), std::to_string(this->_multiplier)};
    std::vector<std::string_view> env;

    kitchen->initKitchen();
    this->_kitchens.emplace(kitchen, process);
    std::cout << "[RECEPTION] Create new kitchen (" << kitchen->getKitchenId() << ")" << std::endl;
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
        (void)process;
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
        std::cout << "Free chiefs: " << (*kitchen->getData())->availableCooks << " / " << this->_cooksNumber << std::endl;
        std::cout << std::string(str.length(), '-') << std::endl;
    }
    plaz::server::PlazzaServerAPIManager().refreshReception(this->getRunningKitchens());
}

void plaz::Reception::quit() {
    for (auto &[kitchen, process] : this->_kitchens) {
        (void)kitchen;
        process->kill(); // TODO @clement, ça ne kill pas le process :/ any idea ?
    }
    std::exit(0);
}

const std::vector<plaz::AKitchen *> plaz::Reception::getRunningKitchens() {
    std::vector<plaz::AKitchen *> runningKitchens;

    for (auto &[kitchen, process] : this->_kitchens) {
        (void)process;
        runningKitchens.push_back(kitchen);
    }
    return runningKitchens;
}
