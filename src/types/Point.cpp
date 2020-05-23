#include "Point.h"

#include "../IsNumber.h"

#include <iostream>

namespace bricks::types {

std::istream &operator>>(std::istream &is, Point &obj)
{
    std::string s;
    is >> s;
    if (s != "X") {
        is.setstate(std::ios_base::failbit);
        return is;
    }

    is >> s;
    if (!isNumber<double>(s)) {
        is.setstate(std::ios_base::failbit);
        return is;
    }
    auto x = std::stod(s);

    is >> s;
    if (s != "Y") {
        is.setstate(std::ios_base::failbit);
        return is;
    }

    is >> s;
    if (!isNumber<double>(s)) {
        is.setstate(std::ios_base::failbit);
        return is;
    }
    auto y = std::stod(s);

    obj.x = x;
    obj.y = y;
    return is;
}
} // namespace bricks::types