/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** main function
*/

#include <thread>

#include "Plazza.hpp"
#include "Pizza.hpp"
#include "Reception.hpp"

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
	if (ac == 4) {
		plaz::Reception reception(av[1], av[2], av[3]);

		reception.receiveOrders();
	} else
		return 84;
	return 0;
}