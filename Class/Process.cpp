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
		} else if (m_p < 0)
			m_error = true;
		else
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
		if (m_p > 0)
			waitpid(m_p, &m_exitcode, 0);
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

void Process::exec()
{
	throw std::logic_error("Not implemented");
}

bool Process::isRunning()
{
	if (m_exitcode == -1) {
		waitpid(m_p, &m_exitcode, WNOHANG);
		m_runing = m_exitcode == -1;
	}
	return m_runing;
}

}

