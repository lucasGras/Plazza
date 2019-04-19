/*
** EPITECH PROJECT, 2018
** Kitchen.cpp
** File description:
** Made by developers
*/

#include <iostream>
#include <thread>
#include <Pizza.hpp>
#include <Kitchen.hpp>

#include "Kitchen.hpp"
#include "Abstractions/DataQueue.hpp"
#include "Abstractions/Thread.hpp"
#include "KitchenData.hpp"

int main(int ac, char **av) {
    if (ac != 5)
        return (84);
    // ARGS: ID - MaxCooks - TimeOut - Multiplier
//    std::cout << "[KITCHEN] Create kitchen " << std::atoi(av[1]) << std::endl;
    plaz::kitchen::Kitchen kitchen(std::atoi(av[1]), std::atoi(av[2]), std::atoi(av[3]), std::atoi(av[4]));
    kitchen.runQueueListen();
    while (true);
}

plaz::kitchen::Kitchen::Kitchen(int kitchenId, int maxCooks, int timeout, int multiplier)
    : AKitchen(kitchenId, maxCooks, timeout, multiplier), _refillStockThread([this]() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(this->getTimeout()));
        this->refillStock();
    }
}), _threadPool(this->getMaxCooks(), (this->getMaxCooks() * 2) - 1, [this](int &pizzaInt) {
    plaz::Pizza pizza{};
    PizzaManager pizzaManager;

	std::cout << std::this_thread::get_id() << ": start pizza lel (" << pizzaInt << ")" << std::endl;
	pizza.unpack(pizzaInt);
    pizza.consumePizza(this->getData());
    std::this_thread::sleep_for(std::chrono::seconds(pizzaManager.getTimeOfCooking(pizza.getType()) * this->getMultiplier()));
    (*this->getData())->availableCooks++;
    std::cout << std::this_thread::get_id() << ": finish pizza lel (" << pizzaInt << ")" << std::endl;
})
{}

void plaz::kitchen::Kitchen::runQueueListen() {
    std::thread thread([this]() {
        while (true) {
            if ((*this->getData())->waitingPizza == -1
                || (*this->getData())->availableCooks <= 0)
                continue;
//            std::cout << "[KITCHEN] [NEW PIZZA] (" << this->getKitchenId() << ") : '" << (*this->getData())->waitingPizza << "'" << std::endl;
            (*this->getData())->availableCooks--;
            _threadPool.queueItem((*this->getData())->waitingPizza);
            (*this->getData())->waitingPizza = -1;
        }
    });
    thread.detach();
}

plaz::kitchen::Kitchen::~Kitchen() {
    this->_refillStockThread.cancel();
}
