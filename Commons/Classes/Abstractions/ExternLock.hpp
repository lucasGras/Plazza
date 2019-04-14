/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** basic pthread conditional variable abstraction
*/

#ifndef EXTERN_LOCK_HPP
#define EXTERN_LOCK_HPP

extern "C" {
	#include <pthread.h>
};

#include <memory>

namespace plaz::abs {

class ExternLock {
public:
	ExternLock();
	ExternLock(const ExternLock &l);
	ExternLock(ExternLock &&l);
	~ExternLock();

	void unlockOne();
	void unlockAll();
	void waitHere() const;

	ExternLock &operator =(const ExternLock &) = delete;
	ExternLock &operator =(ExternLock &&) = delete;
private:
	struct Members {
		pthread_cond_t m_c;
		pthread_mutex_t m_m;
	};
	using SharedMem = const std::shared_ptr<Members>;
private:
	SharedMem m_m = nullptr;
};

}

#endif