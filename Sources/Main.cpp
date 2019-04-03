/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** main function
*/

#include "Plazza.hpp"
#include "Pizza.hpp"
#include <thread>
#include <Reception.hpp>

void Lel()
{
	std::cout << "lel" << std::endl;
}

void Lul()
{
	std::this_thread::yield();
	std::cout << "lul" << std::endl;
}

int main(int, const char *[])
{
	plaz::Reception reception;

    reception.receiveOrders();
	return 0;
}