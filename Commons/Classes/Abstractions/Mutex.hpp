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

}

#include <memory>

namespace plaz::abs {

class Mutex {
public:
	Mutex();
	Mutex(const Mutex &m);
	Mutex(Mutex &&m) noexcept;
	~Mutex();

	bool tryLock();
	void lock();
	void unlock();

	Mutex &operator =(const Mutex &) = delete;
	Mutex &operator =(Mutex &&) = delete;
private:
	struct _Mutex {
		pthread_mutex_t m_m;
	};
	using SharedMutex = std::shared_ptr<_Mutex>;
private:
	SharedMutex m_m = nullptr;
};

}

#endif