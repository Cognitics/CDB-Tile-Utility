
#include "Coordinates.h"

namespace cognitics {
namespace cdb {

Coordinates::Coordinates(void) : _latitude(0.0f), _longitude(0.0f)
{
}

Coordinates::Coordinates(const Latitude& latitude, const Longitude& longitude) : _latitude(latitude), _longitude(longitude)
{
}

Latitude Coordinates::latitude(void) const
{
    return _latitude;
}

Longitude Coordinates::longitude(void) const
{
    return _longitude;
}


} }
