#include "GridHeight.h"

#include "../utility/IsNumber.h"

#include <iostream>
#include <stdexcept>

namespace bricks::types {

using namespace utility;

GridHeight::GridHeight(int value) 
    : mValue{checkArgs(value)}
{
}

int GridHeight::operator()() const
{
    return mValue;
}

int GridHeight::checkArgs(int value) const
{
    if(value < 0) {
        throw std::invalid_argument("GridHeight::checkArgs(int value)\n"
        "Value must be >= 0\n"
        "Value: " + std::to_string(value));
    }
    return value;
}

std::istream& operator>>(std::istream& is, GridHeight& obj)
{
    std::string s;
    is >> s;
    if (s != "H") {
        is.setstate(std::ios_base::failbit);
        return is;
    }

    is >> s;
    if (!isNumber<int>(s)) {
        is.setstate(std::ios_base::failbit);
        return is;
    }
    auto h = std::stoi(s);
    obj = std::move(GridHeight{h});

    return is;
}

} // namespace bricks::types