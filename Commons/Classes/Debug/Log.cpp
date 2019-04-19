#include "Log.hpp"

namespace debug {

LogOstream logOut(std::cout);
LogOstream logErr(std::cerr);

LogOstream::LogOstream(const std::ostream &s)
	: std::ostream(s.rdbuf())
{
	if constexpr (!isDebug) {
		this->_M_streambuf = &m_dumy;
	}
}

LogOstream::LogOstream(std::stringbuf *b)
	: std::ostream(b)
{
	if constexpr (!isDebug) {
		this->_M_streambuf = &m_dumy;
	}
}

}