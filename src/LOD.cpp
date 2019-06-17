
#include "LOD.h"

#include <sstream>
#include <iomanip>
#include <algorithm>

namespace cognitics {
namespace cdb {

LOD::LOD(void) : _value(0)
{
}

LOD::LOD(int8_t value) : _value(value)
{
    _value = std::min<int8_t>(_value, 23);
    _value = std::max<int8_t>(_value, -10);
}

int8_t LOD::value(void) const
{
    return _value;
}

uint32_t LOD::rows(void) const
{
    return std::max<uint32_t>(uint32_t(std::pow(2, _value)), 1);
}

std::string LOD::subdir(void) const
{
    if(_value < 0)
        return "LC";
    std::stringstream ss;
    ss << "L" << std::setw(2) << std::setfill('0') << int(_value);
    return ss.str();
}


} }
