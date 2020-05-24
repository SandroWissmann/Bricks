#include "MaxPositionY.h"

namespace bricks::types {

MaxPositionY::MaxPositionY(double value) : mValue{value}
{
}


double MaxPositionY::operator()() const
{
    return mValue;
}
} // namespace bricks::types