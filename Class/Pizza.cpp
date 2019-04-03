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

    this->_type = static_cast<PizzaType>(1 << std::distance(typeVector.begin(),
            std::find(typeVector.begin(), typeVector.end(), type)));
    this->_size = static_cast<PizzaSize>(1 << std::distance(sizeVector.begin(),
            std::find(sizeVector.begin(), sizeVector.end(), size)));
}

/**
 * @brief create pizza bit mask.
 * We combine the type mask and the size mask by shifting the bytes of BINARY_OFFSET_SIZE
 * which is the maximum bytes a size can take.
 * @return plaz::BitMask
 */
plaz::BitMask plaz::Pizza::pack() {
    BitMask mask = 0;

    mask |= (BitMask)this->_type << BINARY_OFFSET_SIZE;
    mask |= (BitMask)this->_size;
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

plaz::PizzaType plaz::Pizza::getType() {
    return this->_type;
}

plaz::PizzaSize plaz::Pizza::getSize() {
    return this->_size;
}
