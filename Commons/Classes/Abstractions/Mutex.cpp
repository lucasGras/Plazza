/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** pthread mutexes abstraction
*/

#include "Mutex.hpp"

namespace plaz::abs {

Mutex::Mutex()
{
	m_m = PTHREAD_MUTEX_INITIALIZER;
}

Mutex::~Mutex()
{
	pthread_mutex_unlock(&m_m);
	pthread_mutex_destroy(&m_m);
}

bool Mutex::tryLock()
{
	return pthread_mutex_trylock(&m_m) > 0;
}

void Mutex::lock()
{
	pthread_mutex_lock(&m_m);
}

void Mutex::unlock()
{
	pthread_mutex_unlock(&m_m);
}

}