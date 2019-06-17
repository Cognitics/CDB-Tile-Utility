
#include "TileLongitude.h"

#include <algorithm>
#include <sstream>
#include <iomanip>

namespace cognitics {
namespace cdb {

TileLongitude::TileLongitude(void) : _value(0)
{
}

TileLongitude::TileLongitude(const TileLatitude& latitude, int16_t value) : _value(value)
{
    _value = std::min<int16_t>(_value, 179);
    _value = std::max<int16_t>(_value, -180);

    int16_t tile_width = get_tile_width(latitude.value());
    _value /= tile_width;
    _value *= tile_width;
}

TileLongitude::TileLongitude(const TileLatitude& latitude, double value)
{
    *this = TileLongitude(latitude, int16_t(std::floor(value)));
}

TileLongitude::TileLongitude(const TileLatitude& latitude, const Longitude& value)
{
    *this = TileLongitude(latitude, value.value());
}

int16_t TileLongitude::value(void) const
{
    return _value;
}

std::string TileLongitude::subdir(void) const
{
    std::stringstream ss;
    if(_value >= 0)
        ss << "E" << std::setw(3) << std::setfill('0') << _value;
    else
        ss << "W" << std::setw(3) << std::setfill('0') << -_value;
    return ss.str();
}


} }
