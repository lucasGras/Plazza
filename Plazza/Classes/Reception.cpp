/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Created by lucasg,
*/
#include "Reception.hpp"

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

plaz::Reception::Reception(const std::string &multiplier, const std::string &cooks, const std::string &kitchen)
        : _dataQueue("/bigfatcookQueue", O_CREAT | O_WRONLY) {
    this->_multiplier = std::stoi(multiplier);
    this->_cooksNumber = std::stoi(cooks);
    this->_kitchenStockTimeout = std::stoi(kitchen);
}

void plaz::Reception::receiveOrders() {
    std::vector<Order> orders;

    for (std::string line; std::getline(std::cin, line);) {
        auto vector = split(line, ';');

        for (const auto &order : vector) {
            orders.emplace_back(order);
        }
        this->sendOrders(orders);
        orders.clear();
    }
}

void plaz::Reception::sendOrders(std::vector<plaz::Order> orders) {
    this->createKitchen();
    for (auto &order : orders) {
        for (int i = 0; i < order.getAmount(); i++) {
            if (order.isValid()) {
                auto sended = order.getPizza().pack();

                this->_dataQueue.push(std::to_string(sended));
                /*
                auto pizzaOrdered = order.getPizza().unpack(sended);
                std::cout << "receive " << pizzaOrdered.getType() << ", " << pizzaOrdered.getSize() << std::endl;
                 */
            }
        }
    }
}

void plaz::Reception::createKitchen() {
    plaz::abs::Process p;
    std::vector<std::string_view> args{std::to_string(this->_cooksNumber), std::to_string(this->_multiplier),
                                       std::to_string(this->_kitchenStockTimeout), "/bigfatcookSharedData"};
    std::vector<std::string_view> env;

    //this->_sharedData.emplace_back("/bigfatcookSharedData", O_CREAT);
    p.exec(std::string_view("./kitchen"), args, env);
    this->_kitchens.push_back(std::move(p));
}

int plaz::Reception::getMultiplier() {
    return this->_multiplier;
}

int plaz::Reception::getCooksNumber() {
    return this->_cooksNumber;
}

int plaz::Reception::getKitchenStockTimeout() {
    return this->_kitchenStockTimeout;
}
