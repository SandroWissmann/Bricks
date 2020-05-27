#include "GridWidth.h"

#include "../IsNumber.h"

#include <iostream>

namespace bricks::types {

GridWidth::GridWidth(int value) : mValue{value}
{
}

int GridWidth::operator()() const
{
    return mValue;
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