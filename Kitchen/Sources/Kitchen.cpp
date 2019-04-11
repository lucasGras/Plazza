/*
** EPITECH PROJECT, 2018
** Kitchen.cpp
** File description:
** Made by developers
*/

#include <iostream>
#include <thread>
#include <Pizza.hpp>
#include "Kitchen.hpp"
#include "Abstractions/DataQueue.hpp"
#include "KitchenData.hpp"

int main(int ac, char **av) {
    if (ac != 5)
        return (84);
    // ARGS: ID - MaxCooks - TimeOut - Multiplier
    std::cout << "[KITCHEN] Create kitchen " << std::atoi(av[1]) << std::endl;
    plaz::kitchen::Kitchen kitchen(std::atoi(av[1]), std::atoi(av[2]), std::atoi(av[3]), std::atoi(av[4]));
    kitchen.runQueueListen();
}

plaz::kitchen::Kitchen::Kitchen(int kitchenId, int maxCooks, int timeout, int multiplier)
    : AKitchen(kitchenId, maxCooks, timeout, multiplier)
{
    std::thread thread([this]() {
        while (true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(this->getTimeout()));
            this->refillStock();
        }
    });
    thread.detach();
}

void plaz::kitchen::Kitchen::runQueueListen() {
    std::thread thread([this]() {
        while (true) {
            if ((*this->getData())->waitingPizza == -1
                || (*this->getData())->availableCooks <= 0)
                continue;
            plaz::Pizza pizza{};
            pizza.unpack(((*this->getData())->waitingPizza));
            std::cout << "[KITCHEN] [DETECTED PIZZA (" << pizza.getType() << ") ] (" << this->getKitchenId() << ") : '" << (*this->getData())->waitingPizza << "'" << std::endl;
            (*this->getData())->availableCooks--;
            pizza.consumePizza(this->getData());
            std::thread thread([this, pizza]() {
                PizzaManager pizzaManager;
                std::this_thread::sleep_for(std::chrono::seconds(pizzaManager.getTimeOfCooking(pizza.getType()) * this->getMultiplier()));
                (*this->getData())->availableCooks++;
            });
            thread.detach();
            (*this->getData())->waitingPizza = -1;
        }
    });
    thread.join();
}