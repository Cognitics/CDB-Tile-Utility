
#pragma once

#include "Latitude.h"

#include <cstdint>
#include <string>

namespace cognitics {
namespace cdb {

class TileLatitude
{
public:
    TileLatitude(void);
    TileLatitude(int16_t value);
    TileLatitude(double value);
    TileLatitude(const Latitude& value);

    int16_t value(void) const;
    std::string subdir(void) const;

private:
    int16_t _value;
};

int16_t get_tile_width(const TileLatitude& latitude);


} }
