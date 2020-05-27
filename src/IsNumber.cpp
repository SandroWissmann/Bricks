#include <IsNumber.h>

#include <sstream>

namespace bricks {

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
template bool isNumber<double>(const std::string& s);
} // namespace bricks