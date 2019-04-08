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
#include "Abstractions/DataQueue.hpp"
#include "Abstractions/Process.hpp"
#include "Abstractions/SharedData.hpp"

namespace plaz {

    typedef struct shared_data_s {

    } shared_data_t;

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
        plaz::abs::DataQueue<> _dataQueue;
    };
}

#endif //PLAZZA_RECEPTION_HPP
