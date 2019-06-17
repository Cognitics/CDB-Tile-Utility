
#pragma once

#include "Dataset.h"
#include "LODRange.h"
#include "CoordinatesRange.h"
#include "TileCoordinates.h"

#include <cstdint>
#include <vector>
#include <string>

namespace cognitics {
namespace cdb {


struct Tile
{
    TileCoordinates coordinates;
    Dataset dataset;
    LOD lod;
    uint32_t uref;

    std::string str(void);
    std::vector<std::string> vec(void);
};

void generate_tiles(std::vector<Tile>& result, const CoordinatesRange& aoi, const Dataset& dataset, const LODRange& lod_range);





} }
