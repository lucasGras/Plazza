/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** main function
*/

#include "Plazza.hpp"
#include <thread>

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
	std::thread t1(Lul);
	std::thread t2(Lel);
	t1.detach();
	t2.detach();
	std::cout << "ii" << std::endl;
//	t1.join();
//	t2.join();
	return 0;
}