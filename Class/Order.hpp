/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Created by lucasg,
*/
#ifndef PLAZZA_ORDER_HPP
#define PLAZZA_ORDER_HPP

#include <string>
#include <Pizza.hpp>
#include <regex>
#include <iostream>

namespace plaz {
    class Order {
    public:
        Order(const std::string &order);
        ~Order() = default;

        Pizza getPizza();
        bool isValid();
        int getAmount();

    private:
        inline bool isValidOrder(const std::string &order);
        void setPizzaFromOrder(const std::string &order);

    private:
        bool _valid;
        Pizza _pizza;
        int amount;
    };
}

#endif //PLAZZA_ORDER_HPP
