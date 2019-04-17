/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** Thread pool implementation header
*/

#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include <vector>
#include <atomic>
#include <functional>

#include "Thread.hpp"
#include "Mutex.hpp"
#include "Channel.hpp"

namespace plaz::abs {

template<typename T>
class ThreadPool {
public:
	using Procedure = std::function<void(T &)>;
public:
	ThreadPool(std::size_t poolSize, std::size_t queueSize, const Procedure &p)
		: m_chan(queueSize), m_p(p)
	{
		auto threadProc = [this]()
		{
			T obj;
			while (!m_end) {
				if (m_chan.tryPop(obj))
					m_p(obj);
				else
					threadYield();
			}
		};

		for (std::size_t i = 0; i < poolSize; i++)
			m_threads.push_back(new Thread<void>(threadProc));
	}

	ThreadPool(const ThreadPool &) = delete;
	ThreadPool(ThreadPool &&) = delete;
	~ThreadPool()
	{
		m_end = true;
		for (int64_t i = m_threads.size() - 1; i >= 0 ; i--) {
			m_threads[i]->join();
			delete m_threads[i];
			m_threads.pop_back();
		}
	}

	void queueItem(T &&obj)
	{
		m_chan.push(std::move(obj));
	}
private:
	std::atomic_bool m_end = false;
	std::vector<Thread<void> *> m_threads;
	Procedure m_p;
	Channel<T> m_chan;
};

}

#endif