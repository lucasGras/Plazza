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
#include <shared_mutex>
#include <condition_variable>
#include <atomic>

namespace plaz::abs {

template<typename T>
class Channel {
public:
	Channel() = delete;

	Channel(std::size_t size = 1)
		: m_s(size), m_q(new std::queue<T>())
	{
	}

	Channel(const Channel &c)
		: m_s(c.m_s), m_count(std::move(c.m_count)), m_q(c.m_q)
	{
	}

	Channel(Channel &&c) noexcept
		: m_s(c.m_s), m_count(std::move(c.m_count)), m_q(std::move(c.mq))
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
		while (isEmpty())
			std::this_thread::yield();

		m_queueLock.lock_shared();
		T temp = m_q->front();
		m_q->pop();
		m_queueLock.unlock_shared();
		m_count--;
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
		return m_count >= m_s;
	}

	inline bool isEmpty() const noexcept
	{
		return m_count == 0;
	}

private:
	using Queue = std::shared_ptr<std::queue<T>>;
private:
	std::shared_mutex m_queueLock;
	const std::size_t m_s = 1;
	std::atomic_uint64_t m_count = 0;
	Queue m_q = nullptr;
};

}

#endif