/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** test main for abstractions
*/

extern "C" {

#include <fcntl.h>
#include <unistd.h>

}

#include <chrono>
#include <thread>
#include <atomic>

#include "Abstractions/SharedData.hpp"
#include "Abstractions/Process.hpp"

using namespace plaz::abs;

struct Data {
	int a;
	int b;
};

int main(int, char * const [])
{
	SharedData<Data> d("/kek", O_CREAT | O_RDWR, {1, 2});

	Process p;
	std::cerr << "parent: " << getpid() << std::endl;
	p.exec("__test/test", {"/kek"});
//
	std::this_thread::sleep_for(std::chrono::seconds(20));

	return 0;
}