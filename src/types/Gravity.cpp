#include "Gravity.h"

namespace bricks::types {

Gravity::Gravity(double value) : mValue{value}
{
}


double Gravity::operator()() const
{
    return mValue;
}
} // namespace bricks::types