
#include "Longitude.h"

#include <algorithm>

namespace cognitics {
namespace cdb {

Longitude::Longitude(void) : _value(0.0f)
{
}

Longitude::Longitude(double value) : _value(value)
{
    _value = std::min<double>(_value, 180.0f);
    _value = std::max<double>(_value, -180.0f);
}

double Longitude::value(void) const
{
    return _value;
}


} }
