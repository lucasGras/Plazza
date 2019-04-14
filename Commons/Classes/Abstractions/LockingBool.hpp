/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** condtional variable boolean like abstraction header
*/

#ifndef LOCKING_BOOL_HPP
#define LOCKING_BOOL_HPP

extern "C" {

	#include <pthread.h>

}

#include <memory>
#include <atomic>

namespace plaz::abs {

template<bool CONTINUE_VALUE = true, bool CONTINUE_RETURN_VALUE = true>
class LockingBool {
public:
	LockingBool(bool b = false)
		: m_m(new Members{.m_b = b})
	{
		pthread_cond_init(&(m_m->m_c), NULL);
		m_m->m_m = PTHREAD_MUTEX_INITIALIZER;
	}

	LockingBool(const LockingBool &b)
		: m_m(b.m_m)
	{
	}

	LockingBool(LockingBool &&b)
		: m_m(std::move(b.m_m))
	{
	}

	~LockingBool()
	{
		pthread_cond_destroy(&(m_m->m_c));
		pthread_mutex_destroy(&(m_m->m_m));
	}

	inline bool check() const noexcept
	{
		return m_m->m_b;
	}

	inline void waitForChange() const
	{
		pthread_cond_wait(&(m_m->m_c), &(m_m->m_m));
	}

	inline void waitUntilValid() const
	{
		while (m_m->m_b != CONTINUE_VALUE)
			waitForChange();
	}

	inline bool waitAndContinue() const
	{
		waitUntilValid();
		return CONTINUE_RETURN_VALUE;
	}


	inline void silentSet(bool b) noexcept
	{
		m_m->m_b = b;
	}

	inline void set(bool b)
	{
		if (b != m_m->m_b) {
			silentSet(b);
			pthread_cond_signal(&(m_m->m_c));
		}
	}


	LockingBool &operator =(const LockingBool &) = delete;
	LockingBool &operator =(LockingBool &&) = delete;

	inline LockingBool &operator =(bool b)
	{
		set(b);

		return *this;
	}

	inline operator bool() const
	{
		return waitAndContinue();
	}

private:
	struct Members {
		pthread_cond_t m_c;
		pthread_mutex_t m_m;
		std::atomic_bool m_b;
	};
	using SharedMem = const std::shared_ptr<Members>;
private:
	SharedMem m_m = nullptr;
};

}

#endif