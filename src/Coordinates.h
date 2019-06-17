
#pragma once

#include "Latitude.h"
#include "Longitude.h"

namespace cognitics {
namespace cdb {

class Coordinates
{
public:
    Coordinates(void);
    Coordinates(const Latitude& latitude, const Longitude& longitude);

    Latitude latitude(void) const;
    Longitude longitude(void) const;

private:
    Latitude _latitude;
    Longitude _longitude;
};

} }
