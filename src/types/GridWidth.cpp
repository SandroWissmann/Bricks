#include "GridWidth.h"

#include "../utility/IsNumber.h"

#include <iostream>
#include <stdexcept>

namespace bricks::types {

using namespace utility;

GridWidth::GridWidth(int value) : mValue{checkArgs(value)}
{
}

int GridWidth::operator()() const
{
    return mValue;
}

int GridWidth::checkArgs(int value) 
{
    if (value < 0) {
        throw std::invalid_argument("GridWidth::checkArgs(int value)\n"
                                    "Value must be >= 0\n"
                                    "Value: " +
                                    std::to_string(value));
    }
    return value;
}

std::istream& operator>>(std::istream& is, GridWidth& obj)
{
    std::string s;
    is >> s;
    if (s != "W") {
        is.setstate(std::ios_base::failbit);
        return is;
    }

    is >> s;
    if (!isNumber<int>(s)) {
        is.setstate(std::ios_base::failbit);
        return is;
    }
    auto w = std::stoi(s);
    obj = std::move(GridWidth{w});

    return is;
}

} // namespace bricks::types