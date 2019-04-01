/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** posix process abstract header
*/

#include "Process.hpp"

namespace plaz::abs {

void Process::run(Procedure p)
{
	m_p = fork();
	if (m_p == 0) {
		m_exitcode = p();
		_exit(m_exitcode);
	} else if (m_p < 0)
		m_error = true;
}

void Process::kill()
{
	if (m_p > 0)
		::kill(m_p, SIGTERM);
}

bool Process::hasError() const noexcept
{
	return m_error;
}

void Process::wait()
{
	if (m_p > 0)
		waitpid(m_p, &m_exitcode, 0);
}

int Process::getExitCode() const noexcept
{
	return m_exitcode;
}

void Process::exec()
{
	m_p = fork();
	if (m_p == 0) {

	} else if (m_p < 0)
		m_error = true;
}

}

