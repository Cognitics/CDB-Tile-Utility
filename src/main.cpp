
/*
given a source directory, populate a cdb




*/

//#pragma optimize( "", off )

#include "Tile.h"

#include "gdal_priv.h"

#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cstdlib>


int do_error(const std::string& msg)
{
    std::cerr << msg << std::endl;
    return EXIT_FAILURE;
}


////////////////////////////////////////////////////////////////////////////////

/*

/CDB/Metadata/
/CDB/GTModel/
/CDB/MModel/
/CDB/Tiles/
/CDB/Navigation/


*/

namespace cognitics {
namespace cdb {

static const int NbYUnitInCDBGeocell = 1024;    // number of y-axis units for one geocell
static const int NbEarthSlice = 180;            // number of slices along latitude line (each side is one degree)
static const int NbXUnitInGeocell = NbYUnitInCDBGeocell;    // number of x-axis units for one geocell






class TilesPath
{
private:
    double _lat;
    double _lon;
    int _code;

public:

    static const int ELEVATION = 1;
    static const int MIN_MAX_ELEVATION = 2;
    static const int MAX_CULTURE = 3;
    static const int IMAGERY = 4;


    TilesPath(void) : _lat(DBL_MAX), _lon(DBL_MAX)
    {
    }

    TilesPath& lat(double value)
    {
        _lat = value;
        return *this;
    }

    TilesPath& lon(double value)
    {
        _lon = value;
        return *this;
    }

    TilesPath& code(int value)
    {
        _code = value;
        return *this;
    }




};



struct Logger
{
    virtual void write(const std::string& msg) = 0;
    virtual void notice(const std::string& msg) { write(msg); }
    virtual void error(const std::string& msg) { write(msg); }
    virtual void warning(const std::string& msg) { write(msg); }
    virtual void debug(const std::string& msg) { write(msg); }
};

struct ConsoleLogger : public Logger
{
    virtual void write(const std::string& msg)
    {
        std::cout << msg << std::endl;
    }

    virtual void error(const std::string& msg)
    {
        std::cerr << msg << std::endl;
    }
};


// CDB class is a state object representing a CDB
// if a CDB instance exists, it should be a valid path
class CDB
{
public:
    static CDB* open(const std::string& path, Logger* logger = NULL);
    static CDB* create(const std::string& path, Logger* logger = NULL);

private:
    CDB(const std::string& path, Logger* logger);
    std::string path;
    Logger* logger;
};

CDB* CDB::open(const std::string& path, Logger* logger)     // static
{
    if(boost::filesystem::is_directory(path))
        return new CDB(path, logger);
    return NULL;
}

CDB* CDB::create(const std::string& path, Logger* logger)    // static
{
    if(boost::filesystem::exists(path))
        return NULL;
    // TODO
    return NULL;
}

CDB::CDB(const std::string& path, Logger* logger) : path(path), logger(logger)
{
}









} }




namespace cognitics {

/*


*/








}










////////////////////////////////////////////////////////////////////////////////





void process_tif(const std::string& filepath)
{

    GDALDataset* dataset = (GDALDataset*)GDALOpen(filepath.c_str(), GA_ReadOnly);
    if(!dataset)
    {
        std::cout << filepath << ": failed to open dataset" << std::endl;
        return;
    }

    double transform[6];
    dataset->GetGeoTransform(transform);
    double left = transform[0];
    double right = left + transform[1] * dataset->GetRasterXSize();
    double top = transform[3];
    double bottom = top + transform[5] * dataset->GetRasterYSize();

    std::cout << filepath << ": " << dataset->GetRasterXSize() << " x " << dataset->GetRasterYSize() << " x " << dataset->GetRasterCount() << std::endl;
    std::cout << "\tTransform: { " << transform[0] << " , " << transform[1] << " , " << transform[2] << " , " << transform[3] << " , " << transform[4] << " , " << transform[5] << " }" << std::endl;
    std::cout << "\tOrigin: " << transform[0] << " , " << transform[3] << std::endl;
    std::cout << "\tPixelSize: " << transform[1] << " , " << transform[5] << std::endl;
    std::cout << "\tWest: " << left << std::endl;
    std::cout << "\tEast: " << right << std::endl;
    std::cout << "\tNorth: " << top << std::endl;
    std::cout << "\tSouth: " << bottom << std::endl;
    /*
    std::cout << "\tCDB/" << cognitics::cdb::TilesPath()
                                .lat(transform[3])
                                .lon(transform[0])
                                .code(cognitics::cdb::TilesPath::ELEVATION)
                                .str() << std::endl;
                                */

    uint16_t dim_x = 1024;
    uint16_t dim_y = 1024;
    float org_x = 0.0f;
    float org_y = 0.0f;
    float spc_x = 1.0f;
    float spc_y = 1.0f;
    // headersize = 20
    size_t datasize = dim_x * dim_y * sizeof(float);    // 1024 * 1024 * 4 = 4,194,304
    // expected file size = datasize + headersize

    void* data = (float*)malloc(datasize);
    CPLErr result = dataset->RasterIO(GF_Read, 0, 0, dataset->GetRasterXSize(), dataset->GetRasterYSize(), data, dim_x, dim_y, GDT_Float32, 1, NULL, 0, 0, 0);
    if(result == CE_None)
    {
        std::string filename = boost::filesystem::path(filepath).stem().string() + ".cogbin";
        std::cout << "\t-> " << filename << std::endl;
        std::ofstream of(filename, std::ios::out | std::ios::binary);
        of.write((char*)&dim_x, sizeof(dim_x));
        of.write((char*)&dim_y, sizeof(dim_y));
        of.write((char*)&org_x, sizeof(org_x));
        of.write((char*)&org_y, sizeof(org_y));
        of.write((char*)&spc_x, sizeof(spc_x));
        of.write((char*)&spc_y, sizeof(spc_y));
        of.write((char*)data, datasize);
        of.close();
    }
    free(data);

    GDALClose(dataset);
}

void process_files(const std::string& path)
{
    boost::filesystem::path bpath = (path);
    for(boost::filesystem::directory_iterator it(bpath), end; it != end; ++it)
    {
        const boost::filesystem::path& itpath = it->path();
        if(!boost::filesystem::is_regular_file(itpath))
            continue;
        if(itpath.extension() == ".tif")
            process_tif(itpath.string());
    }
}

int main_build_bin(int argc, char** argv)
{
    GDALAllRegister();

    std::string path = (argc >= 2) ? argv[1] : ".";
    boost::filesystem::path bpath = (path);
    if(!boost::filesystem::is_directory(bpath))
        return do_error("invalid directory: " + path);
    process_files(path);

    return EXIT_SUCCESS;
}


int main(int argc, char** argv)
{
    cognitics::cdb::Coordinates coord_min(-90.0, -180.0);
    cognitics::cdb::Coordinates coord_max(90.0, 180.0);
    cognitics::cdb::Dataset ds_elevation(cognitics::cdb::Dataset::Elevation);
    cognitics::cdb::LODRange lod_range(0, 0);

    std::vector<cognitics::cdb::Tile> tiles;
    cognitics::cdb::generate_tiles(tiles, cognitics::cdb::CoordinatesRange(coord_min, coord_max), ds_elevation, lod_range);
    for(size_t i = 0, c = tiles.size(); i < c; ++i)
        std::cout << tiles[i].str() << std::endl;

    return EXIT_SUCCESS;
}


