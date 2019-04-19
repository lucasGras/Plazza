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

#include "Debug/Log.hpp"

namespace plaz::abs {

template<typename T, int PERM = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IROTH>
class SharedData {
public:
	class Mode {
	public:
		enum M : uint8_t {
			None = 0u << 0u,
			Read = 1u << 0u,
			ReadWrite = (1u << 0u) | (1u << 1u),
		};
	public:
		Mode() = default;
		Mode(M m)
			: m_m(m)
		{
		}
		Mode(const Mode &) = default;
		Mode(Mode &&) noexcept = default;
		~Mode() = default;

		Mode &operator =(const Mode &) = default;
		Mode &operator =(Mode &&) noexcept = default;

		constexpr operator M() noexcept
		{
			return m_m;
		}

		constexpr operator uint8_t() noexcept
		{
			return static_cast<uint8_t >(m_m);
		}

		constexpr Mode operator |(Mode m) noexcept
		{
			return static_cast<Mode>(static_cast<uint8_t>(m_m) | static_cast<uint8_t>(m.m_m));
		}

		constexpr Mode operator |=(Mode m) noexcept
		{
			return *this | m;
		}

		constexpr Mode operator &(Mode m) noexcept
		{
			return static_cast<Mode>(static_cast<uint8_t>(m_m) & static_cast<uint8_t>(m.m_m));
		}

		constexpr Mode operator &=(Mode m) noexcept
		{
			return *this | m;
		}

		constexpr bool operator ==(Mode m) noexcept
		{
			return static_cast<uint8_t>(m_m) == static_cast<uint8_t>(m.m_m);
		}

		constexpr bool operator !=(Mode m) noexcept
		{
			return !(*this == m);
		}

		constexpr int asPosix() noexcept
		{
			if ((m_m & ReadWrite) > 0)
				return O_RDWR;
			if ((m_m & Read) > 0)
				return O_RDONLY;

			return 0;
		}
	private:
		M m_m = None;
	};
public:
	SharedData() = delete;
	SharedData(const std::string_view &name, Mode m, bool create = false)
		: m_name(name)
	{
		init(m.asPosix() | (create ? O_CREAT : 0));
	}

	SharedData(const std::string_view &name, const T &obj, Mode m, bool create = false)
		: m_name(name)
	{
		init(m.asPosix() | (create ? O_CREAT : 0));
		*m_typed = obj;
	}

	SharedData(const std::string_view &name, T &&obj, Mode m, bool create = false)
		: m_name(name)
	{
		init(m.asPosix() | (create ? O_CREAT : 0));
		*m_typed = obj;
	}

	//TDOO(ckément): remove those constructors
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

	SharedData &operator <<(const T &obj) noexcept
	{
		return (*this = obj);
	}

	SharedData &operator <<(T &&obj) noexcept
	{
		return (*this = obj);
	}

	SharedData &operator >>(T &obj)
	{
		obj = *m_typed;

		return *this;
	}
private:
	void init(int mode)
	{
		//TODO(clément): clean this up when constructors are cleanned
		if ((mode & O_CREAT) > 0) {
		//TODO(clément): check for fail of shm open and mmap
			m_fd = shm_open(m_name.data(), mode, PERM);
			if (m_fd < 0)
				debug::logErr << "Shared data:" << std::endl << "shm_open failed -> " << debug::cerrno << std::endl;
			if (ftruncate(m_fd, sizeof(T)) < 0)
				debug::logErr << "Shared data:" << std::endl << "ftruncate failed -> " << debug::cerrno << std::endl;
			if ((mode & O_WRONLY) > 0 || (mode & O_RDWR) > 0)
				m_raw = mmap(NULL, sizeof(T), PROT_WRITE | PROT_READ, MAP_SHARED, m_fd, 0);
			else
				m_raw = mmap(NULL, sizeof(T), PROT_READ, MAP_SHARED, m_fd, 0);
			//TODO(clément): do something about this
		} else {
			m_fd = shm_open(m_name.data(), mode, PERM);
			if (m_fd < 0)
				debug::logErr << "Shared data:" << std::endl << "shm_open failed -> " << debug::cerrno << std::endl;
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