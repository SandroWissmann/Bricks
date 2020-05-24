#include "Velocity.h"

namespace bricks::types {

Velocity::Velocity(double value) : mValue{value}
{
}

double Velocity::operator()() const
{
    return mValue;
}
} // namespace bricks::types