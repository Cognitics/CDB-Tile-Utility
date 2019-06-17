
#include "TileLatitude.h"

#include <algorithm>
#include <sstream>
#include <iomanip>

namespace cognitics {
namespace cdb {

TileLatitude::TileLatitude(void) : _value(0)
{
}

TileLatitude::TileLatitude(int16_t value) : _value(value)
{
    _value = std::min<int16_t>(_value, 89);
    _value = std::max<int16_t>(_value, -90);
}

TileLatitude::TileLatitude(double value)
{
    *this = TileLatitude(int16_t(std::floor(value)));
}

TileLatitude::TileLatitude(const Latitude& value)
{
    *this = TileLatitude(value.value());
}

int16_t TileLatitude::value(void) const
{
    return _value;
}

std::string TileLatitude::subdir(void) const
{
    std::stringstream ss;
    if(_value >= 0)
        ss << "N" << std::setw(2) << std::setfill('0') << _value;
    else
        ss << "S" << std::setw(2) << std::setfill('0') << -_value;
    return ss.str();
}

int16_t get_tile_width(const TileLatitude& latitude)
{
    int16_t lat = latitude.value();
    if(lat >= 90.0f)
        return 0;
    if(lat >= 89.0f)
        return 12;
    if(lat >= 80.0f)
        return 6;
    if(lat >= 75.0f)
        return 4;
    if(lat >= 70.0f)
        return 3;
    if(lat >= 50.0f)
        return 2;
    if(lat >= -50.0f)
        return 1;
    if(lat >= -70.0f)
        return 2;
    if(lat >= -75.0f)
        return 3;
    if(lat >= -80.0f)
        return 4;
    if(lat >= -89.0f)
        return 6;
    if(lat >= -90.0f)
        return 12;
    return 0;
}


} }
