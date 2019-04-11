/*
** EPITECH PROJECT, 2018
** AKitchen.cpp
** File description:
** Made by developers
*/

#include "AKitchen.hpp"

plaz::AKitchen::AKitchen(int kitchenId, int maxCooks, int timeout, int multiplier)
        : _kitchenId(kitchenId), _maxCooks(maxCooks), _timeout(timeout), _multiplier(multiplier) {
    this->_sharedData = new plaz::abs::SharedData<KitchenData>("/kitchen_data_" + std::to_string(this->getKitchenId()), O_CREAT | O_RDWR);
    //this->_queue = new plaz::abs::DataQueue("/kitchen_msg_" + std::to_string(this->getKitchenId()), O_CREAT | O_RDWR);
    (*this->getData())->stockHam = 5;
    (*this->getData())->stockDoe = 5;
    (*this->getData())->stockTomato = 5;
    (*this->getData())->stockGruyere = 5;
    (*this->getData())->stockSteak = 5;
    (*this->getData())->stockMushrooms = 5;
    (*this->getData())->stockEggPlant = 5;
    (*this->getData())->stockGoatCheese = 5;
    (*this->getData())->stockChiefLove = 5;
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


