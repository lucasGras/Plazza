/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** pizza abstraction header
*/

#ifndef PIZZA_HPP
#define PIZZA_HPP

#include <string_view>
#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include <functional>
#include "Abstractions/SharedData.hpp"
#include "PizzaManager.hpp"
#include "KitchenData.hpp"

#define BINARY_OFFSET_SIZE 5
#define BINARY_OFFSET_TYPE 32

namespace plaz {

    typedef int BitMask;

    class Pizza {
    public:
        Pizza() = default;
        Pizza(std::string type, std::string size);
        Pizza &operator=(const Pizza &rhs) = default;
        ~Pizza() = default;

        BitMask pack();
        plaz::Pizza unpack(BitMask bitmask);
        PizzaType getType() const;
        PizzaSize getSize() const;
        void consumePizza(plaz::abs::SharedData<KitchenData> *data);
        bool checkCanConsumePizza(plaz::abs::SharedData<KitchenData> *data);

    private:
        PizzaType _type;
        PizzaSize _size;
    };
}

#endif