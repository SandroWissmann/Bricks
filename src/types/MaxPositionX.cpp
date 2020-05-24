#include "MaxPositionX.h"

namespace bricks::types {

MaxPositionX::MaxPositionX(double value) : mValue{value}
{
}


double MaxPositionX::operator()() const
{
    return mValue;
}
} // namespace bricks::types