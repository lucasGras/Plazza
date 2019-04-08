/*
** EPITECH PROJECT, 2018
** Kitchen.hpp
** File description:
** Made by developers
*/

#ifndef PLAZZA_KITCHEN_HPP
#define PLAZZA_KITCHEN_HPP

#include <map>
#include <AKitchen.hpp>
#include <Abstractions/Process.hpp>

namespace plaz::kitchen {
	class Kitchen : public AKitchen {
	public:
		Kitchen(int kitchenId, int maxCooks);
		~Kitchen() = default;

		void runQueueListen();
		std::map<int, plaz::abs::Process> *getCooksProcesses();
	private:
		std::map<int, plaz::abs::Process> *_cooksProcesses;
	};
}
#endif //PLAZZA_KITCHEN_HPP
