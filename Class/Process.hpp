/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** posix process abstract header
*/

#ifndef PROCESS_HPP
#define PROCESS_HPP

extern "C" {

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

}

#include <functional>

namespace plaz::abs {

class Process {
public:
	using Procedure = std::function<int(void)>;
public:
	Process() = default;
	~Process() = default;
	Process(const Process &) = delete;
	Process(Process &&) = delete;
	Process &operator=(const Process &) = delete;
	Process &operator=(Process &&) = delete;

	void run(Procedure p);
	void kill();
	bool hasError() const noexcept;
	int getExitCode() const noexcept;
	void exec();
	void wait();
private:
	pid_t m_p = 0;
	int m_exitcode = 0;
	bool m_running = false;
	bool m_error = false;
};

}

#endif