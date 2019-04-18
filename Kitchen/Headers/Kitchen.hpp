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
#include <Abstractions/Thread.hpp>
#include <Abstractions/ThreadPool.hpp>

#include <fstream>
#include "Debug/Log.hpp"

namespace plaz::kitchen {
	class Kitchen : public AKitchen {
	public:
		Kitchen(int kitchenId, int maxCooks, int timeout, int multiplier);
		~Kitchen();

		void runQueueListen();

	private:
		plaz::abs::Thread<void> _refillStockThread;
		plaz::abs::ThreadPool<int> _threadPool;
	};
}
#endif //PLAZZA_KITCHEN_HPP
