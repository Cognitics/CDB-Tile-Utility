
#pragma once

namespace cognitics {
namespace cdb {

class Longitude
{
public:
    Longitude(void);
    Longitude(double value);

    double value(void) const;

private:
    double _value;
};

} }
