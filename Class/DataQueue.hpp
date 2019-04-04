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

namespace plaz::abs {

template<std::size_t MAX_MSG_SIZE = 1024, std::size_t MAX_MSG = 10, int PERM = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IROTH>
class DataQueue {
public:
	DataQueue() = delete;
	~DataQueue()
	{
		if (m_fd > 0) {
			mq_close(m_fd);
			mq_unlink(m_name.c_str());
		}

	}

	explicit DataQueue(const std::string_view &name, int mode)
	{

//
//		struct sigevent E = {
//			.sigev_notify = SIGEV_NONE,
//		};

		if ((mode & O_CREAT) > 0)
			m_fd = mq_open(name.data(), mode, PERM, &A);
		else
			m_fd = mq_open(name.data(), mode);
		//TODO(clément): check for invalid fd
//		mq_notify(m_fd, &E);
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

	std::string pull()
	{
		ssize_t s = mq_receive(m_fd, buff, MAX_MSG_SIZE, NULL);
		//TODO(clément): check for error (if s < 0)
		return std::string(buff, s);
	}
private:
	constexpr  static struct mq_attr A = {
		.mq_flags = 0,
		.mq_maxmsg = MAX_MSG,
		.mq_msgsize = MAX_MSG_SIZE,
		.mq_curmsgs = 0,
	};
private:
	char buff[MAX_MSG_SIZE];
	const std::string m_name;
	mqd_t m_fd = -1;
};

}

#endif