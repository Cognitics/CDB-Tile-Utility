
#pragma once

#include <cstdint>
#include <string>

namespace cognitics {
namespace cdb {

class LOD
{
public:
    LOD(void);
    LOD(int8_t value);

    int8_t value(void) const;
    uint32_t rows(void) const;
    std::string subdir(void) const;

private:
    int8_t _value;
};

} }
