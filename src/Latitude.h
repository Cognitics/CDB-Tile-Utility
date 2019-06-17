
#pragma once

namespace cognitics {
namespace cdb {

class Latitude
{
public:
    Latitude(void);
    Latitude(double value);

    double value(void) const;

private:
    double _value;
};

} }
