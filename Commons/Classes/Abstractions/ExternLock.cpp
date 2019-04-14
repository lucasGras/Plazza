/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** basic pthread conditional variable abstraction
*/

#include "ExternLock.hpp"

namespace plaz::abs {

ExternLock::ExternLock()
	: m_m(new Members{})
{
	pthread_cond_init(&(m_m->m_c), NULL);
	m_m->m_m = PTHREAD_MUTEX_INITIALIZER;
}

ExternLock::ExternLock(const ExternLock &l)
	: m_m(l.m_m)
{
}

ExternLock::ExternLock(ExternLock &&l)
	: m_m(std::move(l.m_m))
{
}

ExternLock::~ExternLock()
{
	pthread_cond_destroy(&(m_m->m_c));
	pthread_mutex_destroy(&(m_m->m_m));
}

void ExternLock::unlockOne()
{
	pthread_cond_signal(&(m_m->m_c));
}

void ExternLock::unlockAll()
{
	pthread_cond_broadcast(&(m_m->m_c));
}

void ExternLock::waitHere() const
{
	pthread_cond_wait(&(m_m->m_c), &(m_m->m_m));
}

}