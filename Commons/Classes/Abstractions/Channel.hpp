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
		: m_s(c.m_s), m_m(c.m_m), m_l(c.m_l)
	{
	}

	Channel(Channel &&c) noexcept
		: m_s(c.m_s), m_m(std::move(c.m_m)), m_l(std::move(c.m_l))
	{
	}

	~Channel() = default;

	Channel &operator =(const Channel &) = delete;

	Channel &operator =(Channel &&) = delete;

	Channel &operator <<(T &&obj)
	{
		push(obj);

		return *this;
	}

	Channel &operator >>(T &obj)
	{
		obj = pop();

		return *this;
	}

	void push(T &&obj)
	{
		//TODO(clément): replace this with a conditional variable
		while (isFilled())
			threadYield();

		m_l.lock();
		m_m->m_q.push(obj);
		m_l.unlock();
		m_m->m_c++;
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
		//TODO(clément): replace this with a conditional variable

		while (isEmpty())
			threadYield();

		m_l.lock();
		T temp = m_m->m_q.front();
		m_m->m_q.pop();
		m_l.unlock();
		m_m->m_c--;
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
	void waitUntilNotEmpty() const;
	void waitUntilNotFilled() const;
private:
	struct Members {
		std::atomic_uint64_t m_c;
		std::queue<T> m_q;
	};
	using SharedMem = const std::shared_ptr<Members>;
private:
	const std::size_t m_s = 1;
	Mutex m_l;
	SharedMem m_m = nullptr;
};

}

#endif