/*
** EPITECH PROJECT, 2018
** Kitchen.hpp
** File description:
** Made by developers
*/

#ifndef PLAZZA_KITCHEN_HPP
#define PLAZZA_KITCHEN_HPP

#include <Abstractions/SharedData.hpp>

namespace plaz::kitchen {
    class Kitchen {
    public:
        Kitchen(int cooksNumber, int multiplier, int kitchenStockTimeout, const std::string &sharedData);

    private:
        int _multiplier;
        int _cooksNumber;
        int _kitchenStockTimeout;
        //plaz::abs::SharedData<> _sharedData;
    };
}

#endif //PLAZZA_KITCHEN_HPP
