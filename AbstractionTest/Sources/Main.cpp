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

void *jeej(void *in)
{
	pthread_mutex_t *m = (pthread_mutex_t *)in;
	std::cout << pthread_mutex_trylock(m) << std::endl;
	sleepSecond(2);
	std::cout << pthread_mutex_trylock(m) << std::endl;
	sleepSecond(2);
	pthread_mutex_unlock(m);
	return NULL;
}

int main(int, char * const [])
{

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
	pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
	pthread_t t;

	pthread_create(&t, NULL, jeej, &m);
	sleepSecond(1);
	pthread_mutex_lock(&m);
	std::cout << "lel" << std::endl;
	pthread_join(t, NULL);
	return 0;
}