/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Created by lucasg,
*/
#include "Order.hpp"

plaz::Order::Order(const std::string &order) {
    this->_valid = this->isValidOrder(order);
    if (this->_valid) {
        auto parsedOrder = this->getPizzaFromOrder(order);
        this->_pizza = parsedOrder.first;
        this->amount = parsedOrder.second;
    } else {
        this->_pizza = {};
        this->amount = 0;
    }
}

inline bool plaz::Order::isValidOrder(const std::string &order) {
    return std::regex_match(order, std::regex("([a-z|A-Z]+) (S|M|L|XL|XXL) x([1-9][0-9]*)"));
}

std::pair<plaz::Pizza, int> plaz::Order::getPizzaFromOrder(const std::string &order) {
    std::smatch matchs;
    std::regex regex("([a-z|A-Z]+) (S|M|L|XL|XXL) x([1-9][0-9]*)");
    std::vector<std::string> type = {"regina", "margarita", "americana", "fantasia"};
    std::vector<std::string> size = {"S", "M", "L", "XL", "XXL"};
    Pizza pizza{};

    if (std::regex_search(order, matchs, regex)) {
        pizza.type = static_cast<PizzaType>(1 << std::distance(type.begin(), std::find(type.begin(), type.end(), matchs[1])));
        pizza.size = static_cast<PizzaSize>(1 << std::distance(size.begin(), std::find(size.begin(), size.end(), matchs[2])));
    }
    return std::pair<Pizza, int>(pizza, std::stoi(matchs[3]));
}

const plaz::Pizza plaz::Order::getPizza() {
    return this->_pizza;
}

bool plaz::Order::isValid() {
    return this->_valid;
}

int plaz::Order::getAmount() {
    return this->amount;
}
