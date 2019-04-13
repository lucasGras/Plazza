/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** posix thread abstraction header
*/

#ifndef THREAD_HPP
#define THREAD_HPP

extern "C" {

#include <signal.h>
#include <pthread.h>

}

#include <functional>
#include <atomic>
#include <type_traits>
#include <optional>

#include <iostream>

#include <cstring>

namespace plaz::abs {

template<typename RET, bool B, typename ...ARGS>
class ThreadImpl;

template<typename RET, typename ...ARGS>
class ThreadImpl<RET, true, ARGS...> {
public:
	using Procedure = std::function<RET(ARGS...)>;
private:
	struct ProcArgs {
		std::function<RET(void)> p;
		std::atomic_bool *running;
		std::atomic_bool *returned;
		RET *retValue;
	};
public:
	ThreadImpl() = delete;
	ThreadImpl(Procedure p, ARGS &&... args)
	{
		auto procImpl = [](void *a) -> void * {
			ProcArgs *procArgs = static_cast<ProcArgs *>(a);

			int ignore;
			pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &ignore);
			pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, &ignore);

			*(procArgs->running) = true;

			if constexpr (std::is_move_assignable<RET>::value)
				*(procArgs->retValue) = std::move(procArgs->p());
			else
				*(procArgs->retValue) = procArgs->p();
			*(procArgs->returned) = true;
			*(procArgs->running) = false;
			return NULL;
		};

		m_procArgs = ProcArgs{std::bind(p, args...), &m_running, &m_returned, &m_retValue};

		pthread_create(&m_t, NULL, procImpl, &m_procArgs);
	}

	~ThreadImpl() = default;

	ThreadImpl(const ThreadImpl &) = delete;
	ThreadImpl(ThreadImpl &&) = delete;

	void cancel()
	{

		pthread_cancel(m_t);
		pthread_join(m_t, NULL);
		m_running = false;
	}

	void join()
	{
		pthread_join(m_t, NULL);
	}

	void detach()
	{
		pthread_detach(m_t);
	}

	bool isRunning() const noexcept
	{
		return m_running;
	}

	bool hasReturned() const noexcept
	{
		return m_returned;
	}

	inline std::optional<RET> getReturnValue() const noexcept
	{
		if (m_running || !m_returned)
			return std::nullopt;
		return m_retValue;
	}

	ThreadImpl &operator =(const ThreadImpl &) = delete;
	ThreadImpl &operator =(ThreadImpl &&) = delete;
private:
	pthread_t m_t;
	std::atomic_bool m_running = false;
	std::atomic_bool m_returned = false;
	RET m_retValue;
	ProcArgs m_procArgs;
};

template<typename RET, typename ...ARGS>
class ThreadImpl<RET, false, ARGS...> {
public:
	using Procedure = std::function<void(ARGS...)>;
private:
	struct ProcArgs {
		std::function<void(void)> p;
		std::atomic_bool *running;
		std::atomic_bool *returned;
	};
public:
	ThreadImpl() = delete;
	ThreadImpl(Procedure p, ARGS &&... args)
	{
		auto procImpl = [](void *a) -> void * {
			ProcArgs *procArgs = static_cast<ProcArgs *>(a);

			int ignore;
			pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &ignore);
			pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, &ignore);

			*(procArgs->running) = true;
			procArgs->p();
			*(procArgs->returned) = true;
			*(procArgs->running) = false;
			return NULL;
		};

		m_procArgs = ProcArgs{std::bind(p, args...), &m_running, &m_returned};

		pthread_create(&m_t, NULL, procImpl, &m_procArgs);
	}

	~ThreadImpl() = default;

	ThreadImpl(const ThreadImpl &) = delete;
	ThreadImpl(ThreadImpl &&) = delete;

	void cancel()
	{
		if (m_running) {
			pthread_cancel(m_t);
			pthread_join(m_t, NULL);
			m_running = false;
		}
	}

	void join()
	{
		pthread_join(m_t, NULL);
	}

	void detach()
	{
		pthread_detach(m_t);
	}

	bool isRunning() const noexcept
	{
		return m_running;
	}

	bool hasReturned() const noexcept
	{
		return m_returned;
	}

	ThreadImpl &operator =(const ThreadImpl &) = delete;
	ThreadImpl &operator =(ThreadImpl &&) = delete;
private:
	pthread_t m_t;
	std::atomic_bool m_running = false;
	std::atomic_bool m_returned = false;
	ProcArgs m_procArgs;
};

template<typename RET, typename ...ARGS>
using Thread = ThreadImpl<RET,
	(std::is_default_constructible<RET>::value && (std::is_move_assignable<RET>::value || std::is_copy_constructible<RET>::value)),
	ARGS...>;

static inline void threadYield()
{
	pthread_yield();
}

}

#endif