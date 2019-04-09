/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** posix shared memory abstraction header
*/

#ifndef SHARED_DATA_HPP
#define SHARED_DATA_HPP

extern "C" {
	#include <sys/stat.h>
	#include <sys/mman.h>
	#include <fcntl.h>
	#include <unistd.h>
}

#include <string_view>
#include <cstring>
#include <iostream>

namespace plaz::abs {

template<typename T, int PERM = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IROTH>
class SharedData {
public:
	SharedData() = delete;
	SharedData(const std::string_view &name, int mode)
		: m_name(name)
	{
		init(mode);
	}

	SharedData(const std::string_view &name, int mode, const T &obj)
		: m_name(name)
	{
		init(mode);
		*m_typed = obj;
	}

	SharedData(const std::string_view &name, int mode, T &&obj)
		: m_name(name)
	{
		init(mode);
		*m_typed = obj;
	}

	~SharedData()
	{
		if (munmap(m_raw, sizeof(T)) < 0)
			std::cerr << getpid() << " -> munmap: " << strerror(errno) << std::endl;
		if (canUnlink())
			if (shm_unlink(m_name.data()) < 0)
				std::cerr << getpid() << " -> shm_unlink: " << strerror(errno) << std::endl;
		if (close(m_fd) < 0)
			std::cerr << getpid() << " -> close: " << strerror(errno) << std::endl;
	}

	SharedData(const SharedData &) = delete;
	SharedData(SharedData &&) = delete;

	SharedData &operator =(const SharedData &) = delete;
	SharedData &operator =(SharedData &&) = delete;

	inline T &operator *() noexcept
	{
		return *m_typed;
	}

	inline const T &operator *() const noexcept
	{
		return *m_typed;
	}

	inline T *operator ->() noexcept
	{
		return m_typed;
	}

	inline const T *operator ->() const noexcept
	{
		return m_typed;
	}

	SharedData &operator =(T &&obj) noexcept
	{
		*m_typed = obj;
		return *this;
	}

	SharedData &operator =(const T &obj) noexcept
	{
		*m_typed = obj;
		return *this;
	}

private:
	void init(int mode)
	{
		//TODO(clément): convert WRONLY to O_RDWR, can't shm open in write only
		if ((mode & O_CREAT) > 0) {
		//TODO(clément): check for fail of shm open and mmap
			m_fd = shm_open(m_name.data(), mode, PERM);
			ftruncate(m_fd, sizeof(T));
			if ((mode & O_WRONLY) > 0 || (mode & O_RDWR) > 0)
				m_raw = mmap(NULL, sizeof(T), PROT_WRITE | PROT_READ, MAP_SHARED, m_fd, 0);
			else
				m_raw = mmap(NULL, sizeof(T), PROT_READ, MAP_SHARED, m_fd, 0);
			//TODO(clément): do something about this
		} else {
			m_fd = shm_open(m_name.data(), mode, PERM);
			if ((mode & O_WRONLY) > 0 || (mode & O_RDWR) > 0)
				m_raw = mmap(NULL, sizeof(T), PROT_WRITE | PROT_READ, MAP_SHARED, m_fd, 0);
			else
				m_raw = mmap(NULL, sizeof(T), PROT_READ, MAP_SHARED, m_fd, 0);
		}
	}

	bool canUnlink() const
	{
		if (fcntl(m_fd, F_SETLEASE, F_WRLCK) < 0 && errno == EAGAIN)
			return true;

		fcntl(m_fd, F_SETLEASE, F_UNLCK);

		return false;
	}
private:
	union {
		void *m_raw = nullptr;
		T *m_typed;
	};
	int m_fd = -1;
	std::string_view m_name = "";
};

}

#endif