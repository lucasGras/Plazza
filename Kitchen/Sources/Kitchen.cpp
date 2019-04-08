/*
** EPITECH PROJECT, 2018
** Kitchen.cpp
** File description:
** Made by developers
*/

#include <iostream>
#include <thread>
#include "Kitchen.hpp"
#include "Abstractions/SharedData.hpp"
#include "KitchenData.hpp"

int main(int ac, char **av) {
	plaz::abs::SharedData<KitchenData> sharedData("/kitchen01", O_CREAT | O_RDWR);
	while (1) {
		std::cout << "Avaiable Cooks: " << sharedData->avalaibleCooks << std::endl;
		sharedData->avalaibleCooks++;
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
	/*std::cout << "Starting listen DataQueue..." << std::endl;
	plaz::abs::DataQueue queue("/kitchentest", O_CREAT | O_RDWR);
	while (1) {
		std::string response = queue.pull();
		std::cout << "Received message: '" << response << "'" << std::endl;
	}*/
}