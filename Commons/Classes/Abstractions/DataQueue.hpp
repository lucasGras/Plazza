/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** posix message queue abstraction header
*/

#ifndef DATA_QUEUE_HPP
#define DATA_QUEUE_HPP

extern "C" {

#include <mqueue.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

}

#include <cstddef>
#include <string>
#include <string_view>

#include <iostream> //TODO(clément): remove this

namespace plaz::abs {

template<std::size_t MAX_MSG_SIZE = 1024, std::size_t MAX_MSG = 10, int PERM = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IROTH>
class DataQueue {
public:
	class Mode {
	public:
		enum M : uint8_t {
			None = 0u << 0u,
			Read = 1u << 0u,
			Write = 1u << 1u,
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
			if ((m_m & Read) > 0 && (m_m & Write) > 0)
				return O_RDWR;
			if ((m_m & Read) > 0 && (m_m & Write) <= 0)
				return O_RDONLY;
			if ((m_m & Write) > 0 && (m_m & Read) <= 0)
				return O_WRONLY;

			return 0;
		}
	private:
		M m_m = None;
	};
public:
	DataQueue() = delete;
	~DataQueue()
	{
		if (m_fd > 0) {
			mq_close(m_fd);
			mq_unlink(m_name.c_str());
		}

	}

	explicit DataQueue(const std::string_view &name, Mode m, bool create = false)
		: m_name(name)
	{
		init(m.asPosix() | (create ? O_CREAT : 0));
	}

	//TODO(clément): remove this constructor
	explicit DataQueue(const std::string_view &name, int mode)
		: m_name(name)
	{
		init(mode);
	}

	DataQueue(const DataQueue &) = delete;
	DataQueue(DataQueue &&) = delete;

	DataQueue &operator =(const DataQueue &) = delete;
	DataQueue &operator =(DataQueue &&) = delete;

	void push(const std::string_view &msg)
	{
		if (msg.length() > MAX_MSG_SIZE)
			mq_send(m_fd, msg.substr(0, MAX_MSG_SIZE).data(), MAX_MSG_SIZE, 0);
		else
			mq_send(m_fd, msg.data(), msg.length(), 0);
	}

	void push(const std::string &msg)
	{
		if (msg.length() > MAX_MSG_SIZE)
			mq_send(m_fd, msg.substr(0, MAX_MSG_SIZE).c_str(), MAX_MSG_SIZE, 0);
		else
			mq_send(m_fd, msg.c_str(), msg.length(), 0);
	}

	inline void push(const char *msg)
	{
		push(std::string_view(msg));
	}

	//TODO(clément): replaced by pop
	std::string pull()
	{
		ssize_t s = mq_receive(m_fd, buff, MAX_MSG_SIZE, NULL);
		//TODO(clément): check for error (if s < 0)
		return std::string(buff, s);
	}

	std::string pop()
	{
		ssize_t s = mq_receive(m_fd, buff, MAX_MSG_SIZE, NULL);
		//TODO(clément): check for error (if s < 0)
		return std::string(buff, s);
	}

	DataQueue &operator >>(std::string &out)
	{
		out = pop();

		return *this;
	}

	DataQueue &operator <<(const std::string &msg)
	{
		push(msg);
	}

	DataQueue &operator <<(const std::string_view &msg)
	{
		push(msg);
	}

	DataQueue &operator <<(const char *msg)
	{
		push(msg);
	}
private:
	void init(int mode)
	{
		if ((mode & O_CREAT) > 0)
			m_fd = mq_open(m_name.data(), mode, PERM, &A);
		else
			m_fd = mq_open(m_name.data(), mode);

		//TODO(clément): check for invalid fd
				//mq_notify(m_fd, &E);

	}
private:
	constexpr static struct mq_attr A = {
		.mq_flags = 0,
		.mq_maxmsg = MAX_MSG,
		.mq_msgsize = MAX_MSG_SIZE,
		.mq_curmsgs = 0,
	};
	/*constexpr static struct sigevent E = {
		.sigev_notify = SIGEV_NONE,
	};*/

private:
	char buff[MAX_MSG_SIZE];
	const std::string m_name;
	mqd_t m_fd = -1;
};

}

#endif