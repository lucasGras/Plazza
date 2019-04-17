/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** test main for abstractions
*/

extern "C" {

#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

}

#include <chrono>
#include <thread>
#include <atomic>

#include "Abstractions/SharedData.hpp"
#include "Abstractions/Process.hpp"
#include "Abstractions/Thread.hpp"
#include "Abstractions/Channel.hpp"
#include "Abstractions/LockingBool.hpp"
#include "Abstractions/ExternLock.hpp"
#include "Abstractions/DataQueue.hpp"
#include "Abstractions/ThreadPool.hpp"

#include "Debug/Log.hpp"

static inline void sleepSecond(unsigned long s)
{
	std::this_thread::sleep_for(std::chrono::seconds(s));
}

using namespace plaz::abs;

void lel(LockingBool<> &b)
{
	int i = 10;

	while (b) {
		std::cout << i << std::endl;
		i++;
		sleepSecond(1);
	}
}

void jeej(Channel<int> c)
{
	std::cout << c.pop() << std::endl;
	std::cout << c.pop() << std::endl;
	sleepSecond(2);
	std::cout << "waited 2 sec in jeej\n";
	std::cout << c.pop() << std::endl;
	std::cout << c.pop() << std::endl;
	std::cout << c.pop() << std::endl;
	std::cout << c.pop() << std::endl;

}

int main(int, char * const [])
{
	ThreadPool<int> p(2, 3, [](int &i) { std::cout << i << std::endl; });
//	LockingBool<> kek = true;
//
//	Thread<void, LockingBool<> &> t(lel, kek);
//
//	std::cout << "a" << std::endl;
//	sleepSecond(3);
//	kek = false;
//	std::cout << "b" << std::endl;
//	sleepSecond(4);
//	kek = true;
//	sleepSecond(2);
//	t.cancel();

//	Channel<int> c(3);
//	Thread<void, Channel<int>> t(jeej, c);
//
//	c << 0;
//	sleepSecond(2);
//	std::cout << "waited 2 sec in main\n";
//	c << 1;
//
//	c << 2;
//	c << 3;
//	c << 4;
//	std::cout << "try push 5\n";
//	c << 5;
//	std::cout << "pushed 5\n";
//
//	t.join();
//	int i = 0;
//	auto ele = [&i]()
//	{
//		std::cout << i << std::endl;
//		sleepSecond(2);
//	};
//	Worker w;
//	w.setTask(ele);
//	w.runNext();
//	i++;
//	w.setTask(ele);
//	w.runNext();
//	i++;
//	w.setTask(ele);
//	w.runNext();
//	i++;
//	w.setTask(ele);
//	w.runNext();
//	i++;
//	w.runNext();
	int i = 0;
	while (i < 100) {
		p.queueItem(rand());
		p.queueItem(rand());
		p.queueItem(rand());
		p.queueItem(rand());
		sleepSecond(1);
		i++;
	}

	return 0;
}