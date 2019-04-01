/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** pizza abstraction header
*/

#ifndef PIZZA_HPP
#define PIZZA_HPP

#include <string_view>

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

struct Pizza {
	PizzaType t;
	PizzaSize s;
};

}

#endif