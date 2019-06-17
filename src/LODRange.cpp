
#include "LODRange.h"

namespace cognitics {
namespace cdb {

LODRange::LODRange(void)
{
}

LODRange::LODRange(const LOD& min, const LOD& max) : _low(min), _high(max)
{
}

LOD LODRange::low(void) const
{
    return _low.value();
}

LOD LODRange::high(void) const
{
    return _high.value();
}


} }
