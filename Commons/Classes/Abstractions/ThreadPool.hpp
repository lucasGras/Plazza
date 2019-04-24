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

#include "Pizza.hpp"
#include <chrono>
#include <ctime>

#include <fstream>
#include <sstream>

namespace plaz::abs {

template<typename T>
class ThreadPool {
public:
	using Procedure = std::function<void(T &)>;
public:
	ThreadPool(std::size_t poolSize, std::size_t queueSize, const Procedure &p)
		: m_p(p)
	{
		auto threadProc = [this]()
		{
			while (!m_end) {
                if (m_q.size() == 0) {
                    threadYield();
                    continue;
                }
                m_m.lock();
                if (m_q.size() > 0) {
                    T element = m_q.front();
                    m_q.pop();
                    m_m.unlock();
                    m_p(element);
                } else
                    m_m.unlock();
			}
		};
		for (std::size_t i = 0; i < poolSize; i++) {
            auto t = new Thread<void>(threadProc);
            t->detach();
            m_threads.push_back(t);
        }
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
		m_q.push(std::move(obj));
	}
private:
	std::atomic_bool m_end = false;
	std::vector<Thread<void> *> m_threads;
	Procedure m_p;
    Mutex m_m;
	std::queue<T> m_q;
};

}

#endif