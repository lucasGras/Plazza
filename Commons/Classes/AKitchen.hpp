/*
** EPITECH PROJECT, 2018
** AKitchen.hpp
** File description:
** Made by developers
*/

#ifndef PLAZZA_AKITCHEN_HPP
#define PLAZZA_AKITCHEN_HPP

#include <string>
#include "Abstractions/SharedData.hpp"
#include "Abstractions/DataQueue.hpp"
#include "../Structures/KitchenData.hpp"

namespace plaz {
	class AKitchen {
	public:
		AKitchen(int kitchenId, int maxCooks, int timeout, float multiplier);
		~AKitchen() = default;

		int getKitchenId() const;
		int getMaxCooks() const;
		int getMaxSlots() const;
		float getMultiplier() const;
		int getTimeout() const;
		plaz::abs::SharedData<KitchenData> *getData();
		plaz::abs::DataQueue<> *getQueue();
		void initKitchen();
		void refillStock();
		void logMessage(std::string message);
	private:
		int _kitchenId;
		int _maxCooks;
		int _timeout;
		float _multiplier;
		plaz::abs::SharedData<KitchenData> *_sharedData;
        plaz::abs::DataQueue<> *_queue;
	};
}

#endif //PLAZZA_AKITCHEN_HPP
