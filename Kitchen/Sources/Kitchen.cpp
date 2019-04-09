/*
** EPITECH PROJECT, 2018
** Kitchen.cpp
** File description:
** Made by developers
*/

#include <iostream>
#include <thread>
#include "Kitchen.hpp"
#include "Abstractions/DataQueue.hpp"
#include "KitchenData.hpp"

int main(int ac, char **av) {
    if (ac != 4)
        return (84);
    // ARGS: ID - MaxCooks - TimeOut - Multiplier
    std::cout << "[KITCHEN] Create kitchen " << std::atoi(av[0]) << std::endl;
    plaz::kitchen::Kitchen kitchen(std::atoi(av[0]), std::atoi(av[1]), std::atoi(av[2]), std::atoi(av[3]));
    kitchen.runQueueListen();
    while (true);
    /*while (true) {
        std::cout << "Available cooks: " << (*kitchen.getData())->availableCooks << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }*/
}

plaz::kitchen::Kitchen::Kitchen(int kitchenId, int maxCooks, int timeout, int multiplier) : AKitchen(
        kitchenId, maxCooks, timeout, multiplier) {
/*    for (int cook = 0; cook < maxCooks; cook++) {
        this->_cooksProcesses->emplace(cook, plaz::abs::Process());
        (*this->_cooksProcesses)[cook].run([this]() -> int {

        });
    }*/
}

std::map<int, plaz::abs::Process> *plaz::kitchen::Kitchen::getCooksProcesses() {
    return this->_cooksProcesses;
}

void plaz::kitchen::Kitchen::runQueueListen() {
    std::thread thread([this]() {
        plaz::abs::DataQueue queue("/kitchen_msg_" + std::to_string(this->getKitchenId()), O_CREAT | O_RDWR);
        while (1) {
            std::string response = queue.pull();
            (*this->getData())->availableCooks -= 1;
            std::cout << "[KITCHEN] [RECEIVED] (" << this->getKitchenId() << ") : '" << response << "'" << std::endl;
        }
    });
    thread.detach();
}
