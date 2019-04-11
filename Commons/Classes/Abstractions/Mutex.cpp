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
	pthread_mutex_init(&m_m, NULL);
}

Mutex::~Mutex()
{
	pthread_mutex_destroy(&m_m);
}

bool Mutex::tryLock()
{
	return pthread_mutex_trylock(&m_m) > 0;
}

}