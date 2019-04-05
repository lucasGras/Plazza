/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** posix process abstract header
*/

#include "Process.hpp"

#include <iostream>
#include <exception>

namespace plaz::abs {

void Process::run(Procedure p)
{
	if (!m_runing) {
		m_exitcode = -1;
		m_error = false;
		m_p = fork();
		if (m_p == 0) {
			m_exitcode = p();
			_exit(m_exitcode);
		} else if (m_p < 0) {
			m_error = true;
			m_exitcode = 1;
			m_runing = false;
		} else
			m_runing = true;
	}
}

void Process::kill(int code)
{
	if (m_runing) {
		if (m_p > 0) {
			::kill(m_p, code);
			m_exitcode = code;
			m_runing = false;
		}
	}
}

bool Process::hasError() const noexcept
{
	return m_error;
}

void Process::wait()
{
	if (m_runing) {
		if (m_p > 0) {
			waitpid(m_p, &m_exitcode, 0);
			m_runing = false;
		}
	}
}

int Process::getExitCode() noexcept
{
	if (m_exitcode == -1) {
		waitpid(m_p, &m_exitcode, WNOHANG);
		m_runing = m_exitcode == -1;
	}
	return m_exitcode;
}

void Process::exec(const std::string_view &path, const std::vector<std::string_view> &args, const std::vector<std::string_view> &env)
{
	char * _args[args.size() + 1];
	char *_env[env.size() + 1];

	_args[args.size()] = NULL;
	_env[env.size()] = NULL;

	for (std::size_t i = 0; i < args.size(); i++)
		_args[i] = const_cast<char *>(args[i].data());
	for (std::size_t i = 0; i < env.size(); i++)
		_env[i] = const_cast<char *>(env[i].data());

	exec(getAbsolutePath(path).c_str(), _args, _env);
}

bool Process::isRunning()
{
	if (m_exitcode == -1) {
		waitpid(m_p, &m_exitcode, WNOHANG);
		m_runing = m_exitcode == -1;
	}
	return m_runing;
}

void Process::exec(const char *path, char *const *argv, char *const *env)
{
	if (!m_runing) {
		m_exitcode = -1;
		m_error = false;
		m_p = fork();
		if (m_p == 0) {
			if (execve(path, argv, env) < 0)
				_exit(0);
				//TODO(clément): check execve error properly
		} else if (m_p < 0) {
			m_error = true;
			m_exitcode = 1;
			m_runing = false;
		} else if (!m_error && m_p > 0)
			m_runing = true;
	}
}

std::string Process::getAbsolutePath(const std::string_view &relativePath)
{
	char abs[PATH_MAX + 1];

	bzero(abs, (PATH_MAX + 1) * sizeof(char));
	if (realpath(relativePath.data(), abs) == NULL)
		return std::string("");
	else
		return std::string(abs);
}

}

