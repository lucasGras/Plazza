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

void plaz::AKitchen::initKitchen() {
    (*this->getData())->availableCooks = this->getMaxCooks();
    (*this->getData())->waitingPizza = -1;
    (*this->getData())->stockHam = 5;
    (*this->getData())->stockDoe = 5;
    (*this->getData())->stockTomato = 5;
    (*this->getData())->stockGruyere = 5;
    (*this->getData())->stockSteak = 5;
    (*this->getData())->stockMushrooms = 5;
    (*this->getData())->stockEggPlant = 5;
    (*this->getData())->stockGoatCheese = 5;
    (*this->getData())->stockChiefLove = 5;
    (*this->getData())->maxCooks = this->getMaxCooks();
}

void plaz::AKitchen::refillStock() {
    (*this->getData())->stockHam += 1;
    (*this->getData())->stockDoe += 1;
    (*this->getData())->stockTomato += 1;
    (*this->getData())->stockGruyere += 1;
    (*this->getData())->stockSteak += 1;
    (*this->getData())->stockMushrooms += 1;
    (*this->getData())->stockEggPlant += 1;
    (*this->getData())->stockGoatCheese += 1;
    (*this->getData())->stockChiefLove += 1;
}

int plaz::AKitchen::getMultiplier() const {
    return this->_multiplier;
}

int plaz::AKitchen::getTimeout() const {
    return this->_timeout;
}


