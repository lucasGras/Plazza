/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Created by lucasg,
*/
#include "Order.hpp"

namespace plaz {

    Order::Order::Order(const std::string &order) {
        this->_valid = this->isValidOrder(order);
        if (this->_valid) {
            this->setPizzaFromOrder(order);
        } else {
            this->amount = 0;
        }
    }

    inline bool Order::Order::isValidOrder(const std::string &order) {
        return std::regex_match(order, std::regex("([a-z|A-Z]+) (S|M|L|XL|XXL) x([1-9][0-9]*)"));
    }

    void Order::Order::setPizzaFromOrder(const std::string &order) {
        std::smatch matchs;
        std::regex regex("([a-z|A-Z]+) (S|M|L|XL|XXL) x([1-9][0-9]*)");

        std::regex_search(order, matchs, regex);
        this->_pizza = Pizza(matchs[1], matchs[2]);
        this->amount = std::stoi(matchs[3]);
    }

    plaz::Pizza Order::Order::getPizza() {
        return this->_pizza;
    }

    bool Order::Order::isValid() {
        return this->_valid;
    }

    int Order::Order::getAmount() {
        return this->amount;
    }

    std::vector<plaz::Order> Order::getOrdersFromJson(const std::string &jsonstr) {
        auto json = nlohmann::json::parse(jsonstr);
        std::vector<plaz::Order> orders;

        for (auto &elem : json.items()) {
            orders.emplace_back(elem.value());
        }
        return orders;
    }
}