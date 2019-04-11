/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Created by lucasg,
*/

#include <bitset>
#include "Pizza.hpp"

plaz::Pizza::Pizza(std::string type, std::string size) {
    std::vector<std::string> typeVector = {"regina", "margarita", "americana", "fantasia"};
    std::vector<std::string> sizeVector = {"S", "M", "L", "XL", "XXL"};

    this->_type = static_cast<PizzaType>(1 << std::distance(typeVector.begin(), std::find(typeVector.begin(), typeVector.end(), type)));
    this->_size = static_cast<PizzaSize>(1 << std::distance(sizeVector.begin(), std::find(sizeVector.begin(), sizeVector.end(), size)));
}

/**
 * @brief create pizza bit mask.
 * We combine the type mask and the size mask by shifting the bytes of BINARY_OFFSET_SIZE
 * which is the maximum bytes a size can take.
 * @return plaz::BitMask
 */
plaz::BitMask plaz::Pizza::pack() {
    BitMask mask = 0;

    mask |= (BitMask) this->_type << BINARY_OFFSET_SIZE;
    mask |= (BitMask) this->_size;
    return mask;
}

/**
 * @brief Giving a pizza bit mask, it returns the Pizza object wwith the corresponding type and size.
 * By shifting the bit mask by BINARY_OFFSET_SIZE, we can retrieve the pizza type.
 * Then we can retrieve the size in bytes by substract the BINARY_OFFSET_TYPE times type size.
 * @param bitmask plaz::BitMask
 * @return plaz::Pizza
 */
plaz::Pizza plaz::Pizza::unpack(BitMask bitmask) {
    this->_type = static_cast<PizzaType>(bitmask >> BINARY_OFFSET_SIZE);
    this->_size = static_cast<PizzaSize>(bitmask - (BINARY_OFFSET_TYPE * this->_type));
    return *this;
}

plaz::PizzaType plaz::Pizza::getType() const {
    return this->_type;
}

plaz::PizzaSize plaz::Pizza::getSize() const {
    return this->_size;
}

void plaz::Pizza::consumePizza(plaz::abs::SharedData<KitchenData> *data) {
    std::vector<Ingredients> listIngredients = PizzaManager().getIngredientsOf(this->getType());
    for (auto const &ingredient: listIngredients) {
        switch (ingredient) {
            case Doe:
                (*data)->stockDoe -= 1;
                break;
            case Tomato:
                (*data)->stockTomato -= 1;
                break;
            case Gruyere:
                (*data)->stockGruyere -= 1;
                break;
            case Ham:
                (*data)->stockHam -= 1;
                break;
            case Mushrooms:
                (*data)->stockMushrooms -= 1;
                break;
            case Steak:
                (*data)->stockSteak -= 1;
                break;
            case Eggplant:
                (*data)->stockEggPlant -= 1;
                break;
            case GoatCheese:
                (*data)->stockGoatCheese -= 1;
                break;
            case ChiefLove:
                (*data)->stockChiefLove -= 1;
                break;
        }
    }
}


bool plaz::Pizza::checkCanConsumePizza(plaz::abs::SharedData<KitchenData> *data) {
    std::vector<Ingredients> listIngredients = PizzaManager().getIngredientsOf(this->getType());
    std::map<Ingredients, int> actualStock = {
            { Doe, (*data)->stockDoe },
            { Tomato, (*data)->stockTomato },
            { Gruyere, (*data)->stockGruyere },
            { Ham, (*data)->stockHam },
            { Mushrooms, (*data)->stockMushrooms },
            { Steak, (*data)->stockSteak},
            { Eggplant, (*data)->stockEggPlant},
            { GoatCheese, (*data)->stockGoatCheese },
            { ChiefLove, (*data)->stockChiefLove}
    };
    for (auto const &ingredient: listIngredients) {
        if (!actualStock.count(ingredient))
            return false;
        if (actualStock[ingredient] <= 0)
            return false;
    }
    return true;
}
