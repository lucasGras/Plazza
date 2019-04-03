/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Created by lucasg,
*/
#ifndef PLAZZA_RECEPTION_HPP
#define PLAZZA_RECEPTION_HPP

#include <string>
#include <iostream>
#include <vector>
#include <Order.hpp>

namespace plaz {
    class Reception {
    public:
        Reception() = default;
        ~Reception() = default;

        void receiveOrders();
        void sendOrders(std::vector<Order>);
        void createKitchen();
    };
}

#endif //PLAZZA_RECEPTION_HPP
