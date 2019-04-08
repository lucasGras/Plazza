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
        this->setPizzaFromOrder(order);
    } else {
        this->amount = 0;
    }
}

inline bool plaz::Order::isValidOrder(const std::string &order) {
    return std::regex_match(order, std::regex("([a-z|A-Z]+) (S|M|L|XL|XXL) x([1-9][0-9]*)"));
}

void plaz::Order::setPizzaFromOrder(const std::string &order) {
    std::smatch matchs;
    std::regex regex("([a-z|A-Z]+) (S|M|L|XL|XXL) x([1-9][0-9]*)");

    std::regex_search(order, matchs, regex);
    this->_pizza = Pizza(matchs[1], matchs[2]);
    this->amount = std::stoi(matchs[3]);
}

plaz::Pizza plaz::Order::getPizza() {
    return this->_pizza;
}

bool plaz::Order::isValid() {
    return this->_valid;
}

int plaz::Order::getAmount() {
    return this->amount;
}
