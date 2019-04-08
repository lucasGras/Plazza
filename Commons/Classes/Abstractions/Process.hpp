/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** posix process abstract header
*/

#ifndef PROCESS_HPP
#define PROCESS_HPP

extern "C" {

#include <limits.h>
#include <stdlib.h>

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

}

#include <cstring>
#include <vector>
#include <string>
#include <string_view>
#include <functional>
#include <iostream>

namespace plaz::abs {

class Process {
public:
	using Procedure = std::function<int(void)>;
public:
	Process() = default;
	~Process() = default;
	Process(const Process &) = delete;
	Process(Process &&) = default;
	Process &operator=(const Process &) = delete;
	Process &operator=(Process &&) = delete;

	void run(Procedure p);
	void kill(int code = SIGTERM);
	bool hasError() const noexcept;
	int getExitCode() noexcept;
	void wait();
	bool isRunning();
	void exec(const std::string_view &path, const std::vector<std::string_view> &args = {}, const std::vector<std::string_view> &env = {});
	void exec(const char *path, char * const argv[], char * const env[]);
private:
	static std::string getAbsolutePath(const std::string_view &relativePath);
private:
	pid_t m_p = -1;
	bool m_error = false;
	int m_exitcode = -1;
	bool m_runing = false;
};

}

#endif