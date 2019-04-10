/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Created by lucasg,
*/
#ifndef PLAZZA_RECEPTION_HPP
#define PLAZZA_RECEPTION_HPP

#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <Order.hpp>
#include <AKitchen.hpp>
#include "Abstractions/DataQueue.hpp"
#include "Abstractions/Process.hpp"
#include "Abstractions/SharedData.hpp"
#include "PlazzaServerAPIManager.hpp"

namespace plaz {

    class Reception {
    public:
        Reception(const std::string &multiplier, const std::string &cooks, const std::string &timeout);
        ~Reception() = default;

        void receiveOrders();
        void sendOrders(std::vector<Order>);
        void status();
        void quit();
        plaz::AKitchen *getAvailableKitchen(plaz::Pizza);
        plaz::AKitchen *initNewKitchen();

        int getMultiplier();
        int getMaxCooksNumber();
        int getKitchenStockTimeout();
        const std::vector<plaz::AKitchen *> getRunningKitchens();

    private:
        int _multiplier;
        int _cooksNumber;
        int _kitchenStockTimeout;
        std::map<plaz::AKitchen*, plaz::abs::Process*> _kitchens;
    };
}

#endif //PLAZZA_RECEPTION_HPP
