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
#include "../../Commons/Structures/KitchenData.hpp"

int main(int ac, char **av) {
    if (ac != 3)
        return (84);
    plaz::kitchen::Kitchen kitchen(std::atoi(av[1]), std::atoi(av[2]));
    kitchen.runQueueListen();
    while (true) {
        std::cout << "Available cooks: " << (*kitchen.getData())->availableCooks << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

plaz::kitchen::Kitchen::Kitchen(int kitchenId, int maxCooks) : AKitchen(
        kitchenId, maxCooks) {}

std::map<int, plaz::abs::Process> *plaz::kitchen::Kitchen::getCooksProcesses() {
    return this->_cooksProcesses;
}

void plaz::kitchen::Kitchen::runQueueListen() {
    std::thread thread([this]() {
        plaz::abs::DataQueue queue("/kitchen_msg_" + std::to_string(this->getKitchenId()), O_CREAT | O_RDWR);
        while (1) {
            std::string response = queue.pull();
            (*this->getData())->availableCooks++;
            std::cout << "Kitchen " << this->getKitchenId() << "Received message: '" << response << "'" << std::endl;
        }
    });
    thread.detach();
}
