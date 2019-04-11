/*
** EPITECH PROJECT, 2018
** KitchenData.hpp
** File description:
** Made by developers
*/

#ifndef PLAZZA_KITCHENDATA_HPP
#define PLAZZA_KITCHENDATA_HPP

struct KitchenData {
    int availableCooks;
    int waitingPizzas[50] = {
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
    };
    int messageSendingToKitchen = 0;

    int stockDoe;
    int stockTomato;
    int stockGruyere;
    int stockSteak;
    int stockMushrooms;
    int stockHam;
    int stockEggPlant;
    int stockGoatCheese;
    int stockChiefLove;
};

#endif //PLAZZA_KITCHENDATA_HPP
