/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** queue like channel in go header
*/

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

#include "Thread.hpp"
#include "Mutex.hpp"
#include "LockingBool.hpp"


namespace plaz::abs {

template<typename T>
class Channel {
public:
	Channel() = delete;

	Channel(std::size_t size = 1)
		: m_s(size), m_m(new Members{.m_c = 0, .m_q = std::queue<T>()})
	{
	}

	Channel(const Channel &c)
		: m_s(c.m_s), m_m(c.m_m), m_l(c.m_l), m_empty(c.m_empty), m_filled(c.m_filled)
	{
	}

	Channel(Channel &&c) noexcept
		: m_s(c.m_s), m_m(c.m_m), m_l(c.m_l), m_empty(c.m_empty), m_filled(c.m_filled)
	{
	}

	~Channel() = default;

	Channel &operator =(const Channel &) = delete;

	Channel &operator =(Channel &&) = delete;

	Channel &operator <<(T &&obj)
	{
		push(std::move(obj));

		return *this;
	}

	Channel &operator >>(T &obj)
	{
		obj = pop();

		return *this;
	}

	void push(T &&obj)
	{
		m_filled.waitUntilValid();

		m_l.lock();
		m_m->m_q.push(obj);
		m_l.unlock();
		m_m->m_c++;

		m_filled = isFilled();
		m_empty = isEmpty();
	}

	inline bool tryPush(T &&obj)
	{
		if (isFilled())
			return false;
		push(obj);
		return true;
	}

	T pop()
	{
		m_empty.waitUntilValid();

		m_l.lock();
		T temp = m_m->m_q.front();
		m_m->m_q.pop();
		m_l.unlock();
		m_m->m_c--;

		m_filled = isFilled();
		m_empty = isEmpty();

		return std::move(temp);
	}

	inline bool tryPop(T &obj)
	{
		if (isEmpty())
			return false;
		obj = pop();
		return true;
	}

	inline bool isFilled() const noexcept
	{
		return m_m->m_c >= m_s;
	}

	inline bool isEmpty() const noexcept
	{
		return m_m->m_c == 0;
	}
private:
	struct Members {
		std::atomic_uint64_t m_c;
		std::queue<T> m_q;
	};
	using SharedMem = const std::shared_ptr<Members>;
private:
	const std::size_t m_s = 1;
	SharedMem m_m = nullptr;
	Mutex m_l;
	LockingBool<false> m_empty = true;
	LockingBool<false> m_filled = false;
};

}

#endif