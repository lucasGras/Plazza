/*
** EPITECH PROJECT, 2018
** KitchenData.hpp
** File description:
** Made by developers
*/

#ifndef PLAZZA_KITCHENDATA_HPP
#define PLAZZA_KITCHENDATA_HPP

#include <atomic>

struct KitchenData {
    std::atomic_int32_t availableSlots;
    std::atomic_int32_t waitingPizza;
    std::atomic_int32_t stockDoe;
    std::atomic_int32_t stockTomato;
    std::atomic_int32_t stockGruyere;
    std::atomic_int32_t stockSteak;
    std::atomic_int32_t stockMushrooms;
    std::atomic_int32_t stockHam;
    std::atomic_int32_t stockEggPlant;
    std::atomic_int32_t stockGoatCheese;
    std::atomic_int32_t stockChiefLove;
};

#endif //PLAZZA_KITCHENDATA_HPP
