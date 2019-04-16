/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** pthread mutexes abstraction
*/

#include "Mutex.hpp"

#include <iostream> //TODO(clément): remove this

namespace plaz::abs {

Mutex::Mutex()
	: m_m(new _Mutex{})
{
	m_m->m_m = PTHREAD_MUTEX_INITIALIZER;
}

Mutex::Mutex(const Mutex &m)
	: m_m(m.m_m)
{
}

Mutex::Mutex(Mutex &&m) noexcept
	: m_m(m.m_m)
{
	std::cout << "mutex move" << std::endl;
}

Mutex::~Mutex()
{
	pthread_mutex_unlock(&(m_m->m_m));
	pthread_mutex_destroy(&(m_m->m_m));
}

bool Mutex::tryLock()
{
	return pthread_mutex_trylock(&(m_m->m_m)) > 0;
}

void Mutex::lock()
{
	pthread_mutex_lock(&(m_m->m_m));
}

void Mutex::unlock()
{
	pthread_mutex_unlock(&(m_m->m_m));
}

}