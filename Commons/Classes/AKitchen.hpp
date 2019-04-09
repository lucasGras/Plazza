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
		AKitchen(int kitchenId, int maxCooks);
		~AKitchen() = default;

		int getKitchenId() const;
		int getMaxCooks() const;
		plaz::abs::SharedData<KitchenData> *getData();
		plaz::abs::DataQueue<> *getQueue();
	private:
		int _kitchenId;
		int _maxCooks;
		plaz::abs::SharedData<KitchenData> *_sharedData;
        plaz::abs::DataQueue<> *_queue;
	};
}

#endif //PLAZZA_AKITCHEN_HPP
