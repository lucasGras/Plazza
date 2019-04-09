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
};

#include <string_view>
#include <cstring>

namespace plaz::abs {

template<typename T, int PERM = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IROTH>
class SharedData {
public:
	SharedData() = delete;
	SharedData(const std::string_view &name, int mode)
		: m_name(name)
	{

	}

	~SharedData()
	{
		munmap(m_raw, sizeof(T));
		std::cerr << strerror(errno) << std::endl;
		shm_unlink(m_name.data());
		std::cerr << strerror(errno) << std::endl;
		close(m_fd);
		std::cerr << strerror(errno) << std::endl;
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