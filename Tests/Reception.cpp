/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Created by lucasg,
*/

#include <criterion/criterion.h>
#include <Order.hpp>
#include "Pizza.hpp"
#include "../Plazza/Classes/Reception.hpp"

Test(reception, Bitmask0)
{
    plaz::Pizza pizza("regina", "S");
    plaz::Pizza pizza1("margarita", "S");
    plaz::Pizza pizza2("americana", "S");
    plaz::Pizza pizza3("fantasia", "S");

    cr_assert_eq(pizza.pack(), (plaz::BitMask)33);
    cr_assert_eq(pizza1.pack(), (plaz::BitMask)65);
    cr_assert_eq(pizza2.pack(), (plaz::BitMask)129);
    cr_assert_eq(pizza3.pack(), (plaz::BitMask)257);
}

Test(reception, Bitmask1)
{
    plaz::Pizza pizza("regina", "S");
    plaz::Pizza pizza1("margarita", "S");
    plaz::Pizza pizza2("americana", "S");
    plaz::Pizza pizza3("fantasia", "S");

    cr_assert_eq(pizza.unpack(33).getSize(), plaz::PizzaSize::S);
    cr_assert_eq(pizza.unpack(33).getType(), plaz::PizzaType::Regina);
    cr_assert_eq(pizza1.unpack(65).getSize(), plaz::PizzaSize::S);
    cr_assert_eq(pizza1.unpack(65).getType(), plaz::PizzaType::Margarita);
    cr_assert_eq(pizza2.unpack(129).getSize(), plaz::PizzaSize::S);
    cr_assert_eq(pizza2.unpack(129).getType(), plaz::PizzaType::Americana);
    cr_assert_eq(pizza3.unpack(257).getSize(), plaz::PizzaSize::S);
    cr_assert_eq(pizza3.unpack(257).getType(), plaz::PizzaType::Fantasia);
}

Test(reception, regex)
{
    plaz::Order order("regina S x1");
    plaz::Order orderFalse("regina x1");

    cr_assert_eq(order.isValid(), true);
    cr_assert_eq(orderFalse.isValid(), false);
}