#include "Width.h"

#include "../utility/IsNumber.h"

#include <iostream>

namespace bricks::types {

using namespace utility;

Width::Width(double value) : 
    mValue{checkArgs(value)}
{
}

double Width::operator()() const
{
    return mValue;
}

double Width::checkArgs(double value) const
{
    if(value < 0.0) {
        throw std::invalid_argument("Width::checkArgs(int value)\n"
        "Value must be >= 0.0\n"
        "Value: " + std::to_string(value));
    }
    return value;
}

std::istream& operator>>(std::istream& is, Width& obj)
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