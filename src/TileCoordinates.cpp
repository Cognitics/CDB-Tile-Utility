
#include "TileCoordinates.h"

namespace cognitics {
namespace cdb {

TileCoordinates::TileCoordinates(void) : _latitude(0.0f), _longitude(0.0f, 0.0f)
{
}

TileCoordinates::TileCoordinates(const TileLatitude& latitude, const TileLongitude& longitude) : _latitude(latitude), _longitude(longitude)
{
}

TileCoordinates::TileCoordinates(const Latitude& latitude, const Longitude& longitude) : _latitude(latitude.value()), _longitude(latitude.value(), longitude.value())
{
}

TileCoordinates::TileCoordinates(const Coordinates& coordinates) : _latitude(coordinates.latitude().value()), _longitude(_latitude, coordinates.longitude().value())
{
}

TileLatitude TileCoordinates::latitude(void) const
{
    return _latitude;
}

TileLongitude TileCoordinates::longitude(void) const
{
    return _longitude;
}


} }
