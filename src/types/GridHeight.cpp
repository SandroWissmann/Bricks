#include "GridHeight.h"

#include "../IsNumber.h"

#include <iostream>

namespace bricks::types {

GridHeight::GridHeight(int value) : mValue{value}
{
}

int GridHeight::operator()() const
{
    return mValue;
}

std::istream &operator>>(std::istream &is, GridHeight &obj)
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