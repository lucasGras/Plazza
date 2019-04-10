/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Created by lucasg,
*/
#ifndef PLAZZA_PLAZZASERVERAPIMANAGER_HPP
#define PLAZZA_PLAZZASERVERAPIMANAGER_HPP

#include "../../Commons/Vendor/nlohmann/json.hpp"
#include "Reception.hpp"

extern "C" {
    #include <curl/curl.h>
};

#define PLAZZA_SERVER_PORT 3042

namespace plaz::server {

    typedef struct paquet_s {
        int id;
        int available_cooks;
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

        void refreshReception(const std::vector<plaz::AKitchen *>);
    };
}

#endif //PLAZZA_PLAZZASERVERAPIMANAGER_HPP
