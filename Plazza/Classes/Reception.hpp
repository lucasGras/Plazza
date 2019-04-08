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

#include "Order.hpp"
#include "Abstractions/Process.hpp"

namespace plaz {
    class Reception {
    public:
        Reception(const std::string &multiplier, const std::string &cooks, const std::string &timeout);
        ~Reception() = default;

        void receiveOrders();
        void sendOrders(std::vector<Order>);
        void createKitchen();

        int getMultiplier();
        int getCooksNumber();
        int getKitchenStockTimeout();

    private:
        int _multiplier;
        int _cooksNumber;
        int _kitchenStockTimeout;
        std::vector<plaz::abs::Process> _kitchens;
    };
}

#endif //PLAZZA_RECEPTION_HPP
