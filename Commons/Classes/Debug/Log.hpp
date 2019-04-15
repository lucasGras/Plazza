/*
** EPITECH PROJECT, 2018
** logger
** File description:
** stream style logger header
*/

#ifndef LOG_HPP
#define LOG_HPP

extern "C" {
	#include <sys/types.h>
	#include <unistd.h>
};

#include <iostream>
#include <sstream>
#include <cstring>
#include <cerrno>

namespace debug {

class LogOstream final : public std::ostream {
public:
	LogOstream() = delete;
	LogOstream(const std::ostream &s);
	LogOstream(std::stringbuf *s);
	LogOstream(const LogOstream &) = delete;
	LogOstream(LogOstream &&) = delete;
	virtual ~LogOstream() = default;

	LogOstream &operator =(const LogOstream &) = delete;
	LogOstream &operator =(LogOstream && ) = delete;
private:
#if defined(DEBUG) && DEBUG == 1
	constexpr static bool isDebug = true;
#else
	constexpr static bool isDebug = false;
#endif
	std::stringbuf m_dumy;
};

extern LogOstream logOut;
extern LogOstream logErr;

inline static std::ostream &cerrno(std::ostream &s)
{
	return s << strerror(errno);
}

inline static std::ostream &pid(std::ostream &s)
{
	return s << getpid();
}

}

#endif