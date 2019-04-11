/*
** EPITECH PROJECT, 2018
** PizzaManager.hpp
** File description:
** Made by developers
*/

#ifndef PLAZZA_PIZZAMANAGER_HPP
#define PLAZZA_PIZZAMANAGER_HPP

#include <map>
#include <vector>

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
        Tomato,
        Gruyere,
        Ham,
        Mushrooms,
        Steak,
        Eggplant,
        GoatCheese,
        ChiefLove,
    };

    class PizzaManager {
    public:
        PizzaManager() = default;
        ~PizzaManager() = default;

        inline std::vector<Ingredients> getIngredientsOf(PizzaType pizza) {
            return _ingredientsOfPizza[pizza];
        }
        inline int getTimeOfCooking(PizzaType pizzaType) {
            return _timesOfPizza[pizzaType];
        }
    private:
        std::map<PizzaType, std::vector<Ingredients>> _ingredientsOfPizza = {
                { Margarita, { Doe, Tomato, Gruyere } },
                { Regina, { Doe, Tomato, Gruyere, Ham, Mushrooms } },
                { Americana, { Doe, Tomato, Gruyere, Steak } },
                { Fantasia, { Doe, Tomato, Eggplant, GoatCheese, ChiefLove } }
        };
        std::map<PizzaType, int> _timesOfPizza = {
                { Regina, 1 },
                { Regina, 2 },
                { Americana, 2 },
                { Fantasia, 4 },
        };
    };

}

#endif //PLAZZA_PIZZAMANAGER_HPP
