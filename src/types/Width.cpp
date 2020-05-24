#include "Width.h"

#include "../IsNumber.h"

#include <iostream>

namespace bricks::types {

Width::Width(double value) : mValue{value}
{
}

double Width::operator()() const
{
    return mValue;
}

std::istream &operator>>(std::istream &is, Width &obj)
{
    std::string s;
    is >> s;
    if (s != "W") {
        is.setstate(std::ios_base::failbit);
        return is;
    }

    is >> s;
    if (!isNumber<double>(s)) {
        is.setstate(std::ios_base::failbit);
        return is;
    }
    auto w = std::stod(s);
    obj = std::move(Width{w});

    return is;
}

} // namespace bricks::types