#include "Height.h"

#include "../utility/IsNumber.h"

#include <iostream>

namespace bricks::types {

using namespace utility;

Height::Height(double value) : mValue{value}
{
}

double Height::operator()() const
{
    return mValue;
}

std::istream& operator>>(std::istream& is, Height& obj)
{
    std::string s;
    is >> s;
    if (s != "H") {
        is.setstate(std::ios_base::failbit);
        return is;
    }

    is >> s;
    if (!isNumber<double>(s)) {
        is.setstate(std::ios_base::failbit);
        return is;
    }
    auto h = std::stod(s);
    obj = std::move(Height{h});

    return is;
}

} // namespace bricks::types