/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** main function
*/

#include <thread>
#include <KitchenData.hpp>

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
	plaz::abs::SharedData<KitchenData> sharedData("/kitchen01", O_CREAT | O_RDWR);
	while (1) {
		std::cout << "Avaiable Cooks: " << sharedData->avalaibleCooks << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
	/*plaz::abs::DataQueue queue("/kitchentest", O_CREAT | O_RDWR);
	for (int i = 0; i <= 10000; i++)
		queue.push("Salut ça va ?");*/
	/*plaz::Reception reception(av[1], av[2], av[3]);
	reception.receiveOrders();
	return 0;*/
}