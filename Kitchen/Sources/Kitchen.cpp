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

	pizza.unpack(pizzaInt);
    pizza.consumePizza(this->getData());
    std::this_thread::sleep_for(std::chrono::seconds(pizzaManager.getTimeOfCooking(pizza.getType()) * this->getMultiplier()));
    (*this->getData())->availableCooks++;
    this->_queueLog.push("Kitchen " + std::to_string(this->getKitchenId()) + " : finished pizza " + std::to_string(pizzaInt));
}), _queueLog("/plazzaLog", plaz::abs::DataQueue<>::Mode::Write), _queueTimeout("/plazzaTimeout", plaz::abs::DataQueue<>::Mode::Write)
{}

void plaz::kitchen::Kitchen::runQueueListen() {
    std::thread thread([this]() {
        auto start = std::chrono::system_clock::now();
        bool isworking = true;

        while (true) {
            int elapsed_seconds = static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(
                    std::chrono::system_clock::now() - start).count());

            if ((*this->getData())->availableCooks == this->getMaxCooks() && isworking) {
                start = std::chrono::system_clock::now();
                isworking = false;
            }
            if (elapsed_seconds >= 5 && (*this->getData())->availableCooks == this->getMaxCooks() && !isworking) {
                this->_queueTimeout.push(std::to_string(this->getKitchenId()));
                exit(0);
            }
            if ((*this->getData())->waitingPizza == -1
                || (*this->getData())->availableCooks <= 0)
                continue;
            isworking = true;
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
