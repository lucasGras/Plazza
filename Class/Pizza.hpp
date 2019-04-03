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

#define BINARY_OFFSET_SIZE 5
#define BINARY_OFFSET_TYPE 32

namespace plaz {

    enum PizzaType {
        Regina = 1 << 0,
        Margarita = 1 << 1,
        Americana = 1 << 2,
        Fantasia = 1 << 3,
    };

    enum PizzaSize {
        S = 1 << 0,
        M = 1 << 1,
        L = 1 << 2,
        XL = 1 << 3,
        XXL = 1 << 4,
    };

    enum Ingredients : std::size_t {
        Doe,
        Tomota,
        Gruyere,
        Ham,
        Mushrooms,
        Steak,
        Eggplant,
        GoatCheese,
        ChiefLove,
    };

    typedef int BitMask;

    class Pizza {
    public:
        Pizza() = default;
        Pizza(std::string type, std::string size);
        Pizza &operator=(const Pizza &rhs) = default;
        ~Pizza() = default;

        BitMask pack();
        plaz::Pizza unpack(BitMask bitmask);
        PizzaType getType();
        PizzaSize getSize();

    private:
        PizzaType _type;
        PizzaSize _size;
    };
}

#endif