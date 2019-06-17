
#pragma once

#include "LOD.h"

namespace cognitics {
namespace cdb {

class LODRange
{
public:
    LODRange(void);
    LODRange(const LOD& min, const LOD& max);

    LOD low(void) const;
    LOD high(void) const;

private:
    LOD _low;
    LOD _high;
};




} }
