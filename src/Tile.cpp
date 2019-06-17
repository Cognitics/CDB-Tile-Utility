
#include "Tile.h"

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>

namespace cognitics {
namespace cdb {



std::string get_uref_subdir(uint32_t uref)
{
    std::stringstream ss;
    ss << "U" << uref;
    return ss.str();
}



////////////////////////////////////////////////////////////////////////////////

std::string Tile::str(void)
{
    std::vector<std::string> dirs = vec();
    return dirs[0] + "/" + dirs[1] + "/" + dirs[2] + "/" + dirs[3] + "/" + dirs[4];
}

std::vector<std::string> Tile::vec(void)
{
    std::vector<std::string> result(5);
    result[0] = coordinates.latitude().subdir();
    result[1] = coordinates.longitude().subdir();
    result[2] = dataset.subdir();
    result[3] = lod.subdir();
    result[4] = get_uref_subdir(uref);
    return result;
}

////////////////////////////////////////////////////////////////////////////////

void generate_tiles(std::vector<Tile>& result, const CoordinatesRange& aoi, const Dataset& dataset, const LODRange& lod_range)
{
    const Coordinates aoi_min = aoi.low();
    const Coordinates aoi_max = aoi.high();
    const TileLatitude lat_min(aoi_min.latitude());
    const TileLatitude lat_max(aoi_max.latitude());
    const TileLongitude lon_min(0.0f, aoi_min.longitude());
    const TileLongitude lon_max(0.0f, aoi_max.longitude());
    const LOD lod_min = lod_range.low();
    const LOD lod_max = lod_range.high();

    Tile tile;
    tile.dataset = dataset;
    for(int8_t ilod = lod_max.value(), ilod_min = lod_min.value(); ilod >= ilod_min; --ilod)
    {
        tile.lod = ilod;
        for(int16_t ilat = lat_min.value(), ilat_max = lat_max.value(); ilat <= ilat_max; ++ilat)
        {
            int16_t ilon_step = cognitics::cdb::get_tile_width(TileLatitude(ilat));
            for(int16_t ilon = lon_min.value(), ilon_max = lon_max.value(); ilon <= ilon_max; ilon += ilon_step)
            {
                tile.coordinates = Coordinates(ilat, ilon);
                for(uint32_t uref = 0, uref_rows = tile.lod.rows(); uref < uref_rows; ++uref)
                {
                    tile.uref = uref;
                    result.push_back(tile);
                }
            }
        }

    }
}




// LatLon_Dnnn_Snnn_Tnnn_LOD_Un_Rn.xxx (p117)



/*

double lat_min = -DBL_MAX;
double lon_min = -DBL_MAX;
double lat_max = DBL_MAX;
double lon_max = DBL_MAX;
std::vector<Tile> tiles;
cognitics::cdb::generate_tiles(tiles, lat_min, lon_min, lat_max, lon_max);




*/






} }
