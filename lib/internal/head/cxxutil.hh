#ifndef CXXUTIL_HH_
#define CXXUTIL_HH_

#include <sstream>
#include <string>
#include <system_error>

template <typename T>
inline std::string
toStr(const T &n)
{
	std::ostringstream stm;
	stm << n;
	return stm.str();
}

#endif /* CXXUTIL_HH_ */
