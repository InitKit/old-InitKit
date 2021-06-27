#include <sstream>
#include <string>

template <typename T> inline std::string toStr(const T &n)
{
    std::ostringstream stm;
    stm << n;
    return stm.str();
}
