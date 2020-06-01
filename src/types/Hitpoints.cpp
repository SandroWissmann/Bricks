#include "Hitpoints.h"

#include "../utility/IsNumber.h"

#include <iostream>

namespace bricks::types {

using namespace utility;

Hitpoints::Hitpoints(int value) : 
    mValue{checkArgs(value)}
{
}

int Hitpoints::operator()() const
{
    return mValue;
}

int Hitpoints::checkArgs(int value) const
{
    if(value < 0) {
        throw std::invalid_argument("Hitpoints::checkArgs(int value)\n"
        "Value must be >= 0\n"
        "Value: " + std::to_string(value));
    }
    return value;
}

std::istream& operator>>(std::istream& is, Hitpoints& obj)
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