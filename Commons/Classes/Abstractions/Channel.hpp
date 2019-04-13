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
		: m_s(size), m_c(new std::atomic_uint64_t(0)), m_q(new std::queue<T>()), m_l(new Mutex())
	{
	}

	Channel(const Channel &c)
		: m_s(c.m_s), m_c(c.m_c), m_q(c.m_q), m_l(c.m_l)
	{
	}

	Channel(Channel &&c) noexcept
		: m_s(c.m_s), m_c(std::move(c.m_c)), m_q(std::move(c.m_q)), m_l(std::move(c.m_l))
	{
	}

	~Channel() = default;

	Channel &operator =(const Channel &) = delete;

	Channel &operator =(Channel &&) = delete;

	Channel &operator <<(T &&obj)
	{
		push(obj);
	}

	Channel &operator >>(T &obj)
	{
		obj = pop();
	}

	void push(T &&obj)
	{
		//TODO(clément): replace this with a conditional variable
		while (isFilled())
			threadYield();

		m_l->lock();
		m_q->push(obj);
		m_l->unlock();
		(*m_c)++;
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

		m_l->lock();
		T temp = m_q->front();
		m_q->pop();
		m_l->unlock();
		(*m_c)--;
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
		return (*m_c) >= m_s;
	}

	inline bool isEmpty() const noexcept
	{
		return *(m_c) == 0;
	}

private:
	//TODO(clément): find a better workaround
	using Counter = std::shared_ptr<std::atomic_uint64_t>;
	using Queue = std::shared_ptr<std::queue<T>>;
	using Lock = std::shared_ptr<Mutex>;
private:
	const std::size_t m_s = 1;
	Counter m_c = nullptr;
	Queue m_q = nullptr;
	Lock m_l = nullptr;

};

}

#endif