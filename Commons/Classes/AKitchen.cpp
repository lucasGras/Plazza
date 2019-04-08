/*
** EPITECH PROJECT, 2018
** AKitchen.cpp
** File description:
** Made by developers
*/

#include "AKitchen.hpp"

plaz::AKitchen::AKitchen(int kitchenId, int maxCooks)
        : _kitchenId(kitchenId), _maxCooks(maxCooks) {
    this->_sharedData = new plaz::abs::SharedData<KitchenData>("/kitchen_data_" + std::to_string(this->getKitchenId()), O_CREAT | O_RDWR);
    this->_queue = new plaz::abs::DataQueue("/kitchen_msg_" + std::to_string(this->getKitchenId()), O_CREAT | O_RDWR);
}

int plaz::AKitchen::getKitchenId() const {
    return this->_kitchenId;
}

int plaz::AKitchen::getMaxCooks() const {
    return this->_maxCooks;
}

plaz::abs::SharedData<KitchenData> *plaz::AKitchen::getData() {
    return this->_sharedData;
}

plaz::abs::DataQueue<> *plaz::AKitchen::getQueue() {
    return this->_queue;
}


