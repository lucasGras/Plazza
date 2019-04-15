/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Created by lucasg,
*/
#ifndef PLAZZA_PLAZZASERVERAPIMANAGER_HPP
#define PLAZZA_PLAZZASERVERAPIMANAGER_HPP

extern "C" {
    #include <curl/curl.h>
};

#include "../../Commons/Vendor/nlohmann/json.hpp"
#include "Reception.hpp"

#define PLAZZA_SERVER_PORT 3042

namespace plaz::server {

    typedef struct paquet_s {
        int id;
        int max_cooks;
        int available_cooks;
        int waiting_pizza;
        int stockDoe;
        int stockTomato;
        int stockGruyere;
        int stockSteak;
        int stockMushrooms;
        int stockHam;
        int stockEggPlant;
        int stockGoatCheese;
        int stockChiefLove;
    } paquet_t;

    class PlazzaServerAPIManager {
    public:
        PlazzaServerAPIManager() = default;
        ~PlazzaServerAPIManager() = default;

        void refreshReception(std::vector<plaz::AKitchen *>);
        std::vector<plaz::Order> getOrders();

        void runApi(plaz::Reception *reception, std::string timer);
    };
}

#endif //PLAZZA_PLAZZASERVERAPIMANAGER_HPP
