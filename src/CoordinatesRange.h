
#pragma once

#include "Coordinates.h"

namespace cognitics {
namespace cdb {

class CoordinatesRange
{
public:
    CoordinatesRange(void);
    CoordinatesRange(const Coordinates& min, const Coordinates& max);

    Coordinates low(void) const;
    Coordinates high(void) const;

private:
    Coordinates _low;
    Coordinates _high;
};

} }
