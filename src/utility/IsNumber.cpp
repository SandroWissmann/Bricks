#include <IsNumber.h>

#include <sstream>

namespace bricks::utility {

template <typename T> bool isNumber(const std::string& s)
{
    if (s.empty()) {
        return false;
    }

    std::istringstream ist(s);
    T n;
    ist >> std::noskipws >> n;

    return ist.eof() && !ist.fail();
}

template bool isNumber<int>(const std::string& s);
template bool isNumber<std::size_t>(const std::string& s);
template bool isNumber<long long>(const std::string& s);
template bool isNumber<double>(const std::string& s);
} // namespace bricks::utility