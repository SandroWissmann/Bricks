#include "Length.h"

#include "../IsNumber.h"

#include <iostream>

namespace bricks::types {

Length::Length(double value) : mValue{value}
{
}

double Length::operator()() const
{
    return mValue;
}

std::istream &operator>>(std::istream &is, Length &obj)
{
    std::string s;
    is >> s;
    if (s != "L") {
        is.setstate(std::ios_base::failbit);
        return is;
    }

    is >> s;
    if (!isNumber<double>(s)) {
        is.setstate(std::ios_base::failbit);
        return is;
    }
    auto w = std::stod(s);
    obj = std::move(Length{w});

    return is;
}

} // namespace bricks::types