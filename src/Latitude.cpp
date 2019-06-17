
#include "Latitude.h"

#include <algorithm>

namespace cognitics {
namespace cdb {

Latitude::Latitude(void) : _value(0.0f)
{
}

Latitude::Latitude(double value) : _value(value)
{
    _value = std::min<double>(_value, 90.0f);
    _value = std::max<double>(_value, -90.0f);
}

double Latitude::value(void) const
{
    return _value;
}


} }
