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
    std::stringstream ss (s);
    std::string item;

    while (getline(ss, item, delim)) {
        ltrim(item);
        rtrim(item);
        result.push_back(item);
    }
    return result;
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
    for (auto &order : orders) {
        for (int i = 0; i < order.getAmount(); i++) {
            if (order.isValid())
                std::cout << "send " << order.getPizza().type << ", " << order.getPizza().size << std::endl;
        }
    }
}
