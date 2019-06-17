
#include "CoordinatesRange.h"

namespace cognitics {
namespace cdb {

CoordinatesRange::CoordinatesRange(void)
{
}

CoordinatesRange::CoordinatesRange(const Coordinates& min, const Coordinates& max) : _low(min), _high(max)
{
}

Coordinates CoordinatesRange::low(void) const
{
    return _low;
}

Coordinates CoordinatesRange::high(void) const
{
    return _high;
}



} }
