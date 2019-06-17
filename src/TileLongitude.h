
#pragma once

#include "TileLatitude.h"
#include "Longitude.h"

namespace cognitics {
namespace cdb {

class TileLongitude
{
public:
    TileLongitude(void);
    TileLongitude(const TileLatitude& latitude, int16_t value);
    TileLongitude(const TileLatitude& latitude, double value);
    TileLongitude(const TileLatitude& latitude, const Longitude& value);

    int16_t value(void) const;
    std::string subdir(void) const;

private:
    int16_t _value;
};

} }
