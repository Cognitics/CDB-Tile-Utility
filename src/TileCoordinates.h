
#pragma once

#include "Coordinates.h"
#include "TileLatitude.h"
#include "TileLongitude.h"

namespace cognitics {
namespace cdb {

class TileCoordinates
{
public:
    TileCoordinates(void);
    TileCoordinates(const TileLatitude& latitude, const TileLongitude& longitude);
    TileCoordinates(const Latitude& latitude, const Longitude& longitude);
    TileCoordinates(const Coordinates& coordinates);

    TileLatitude latitude(void) const;
    TileLongitude longitude(void) const;

private:
    TileLatitude _latitude;
    TileLongitude _longitude;
};

} }
