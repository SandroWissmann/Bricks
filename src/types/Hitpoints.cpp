#include "Hitpoints.h"

#include "../IsNumber.h"

#include <iostream>

namespace bricks::types {

Hitpoints::Hitpoints(int value) : mValue{value}
{
}

int Hitpoints::operator()() const
{
    return mValue;
}

std::istream &operator>>(std::istream &is, Hitpoints &obj)
{
    std::string s;
    is >> s;
    if (s != "HP") {
        is.setstate(std::ios_base::failbit);
        return is;
    }

    is >> s;
    if (!isNumber<int>(s)) {
        is.setstate(std::ios_base::failbit);
        return is;
    }
    auto hp = std::stoi(s);
    obj = std::move(Hitpoints{hp});

    return is;
}

} // namespace bricks::types