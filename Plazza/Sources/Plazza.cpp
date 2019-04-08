/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** main function
*/

#include <thread>
#include <KitchenData.hpp>
#include <Abstractions/DataQueue.hpp>
#include <AKitchen.hpp>

#include "Plazza.hpp"
#include "Pizza.hpp"
#include "Reception.hpp"
#include "Abstractions/SharedData.hpp"

void Lel()
{
	std::cout << "lel" << std::endl;
}

void Lul()
{
	std::this_thread::yield();
	std::cout << "lul" << std::endl;
}

int main(int ac, const char **av)
{
	if (ac != 4)
		return (84);
    plaz::AKitchen kitchen(1, 3);
    kitchen.getQueue()->push("tamerelapute");

	//std::cout << "Avaiable Cooks: " << kitchen.getData()->operator*().availableCooks << std::endl;

	/*plaz::abs::SharedData<KitchenData> sharedData("/kitchen01", O_CREAT | O_RDWR);
	while (1) {
		std::cout << "Avaiable Cooks: " << sharedData->avalaibleCooks << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}*/
	/*plaz::Reception reception(av[1], av[2], av[3]);
	reception.receiveOrders();
	return 0;*/
}