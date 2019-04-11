/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** pthread mutexes abstraction header
*/

#ifndef MUTEX_HPP
#define MUTEX_HPP

extern "C" {

	#include <pthread.h>

};

namespace plaz::abs {

class Mutex {
public:
	Mutex();
	Mutex(const Mutex &) = delete;
	Mutex(Mutex &&) = delete;
	~Mutex();

	bool tryLock();
	void lock();
	void unlock();

	Mutex &operator =(const Mutex &) = delete;
	Mutex &operator =(Mutex &&) = delete;
private:
	pthread_mutex_t m_m;
};

}

#endif