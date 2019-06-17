
#pragma once

#include <cstdint>
#include <string>
#include <map>

namespace cognitics {
namespace cdb {

std::map<int, const char*> get_datasets_map_by_code(void);
std::map<const char*, int> get_datasets_map_by_name(void);
const char* get_dataset_name_by_code(uint16_t code);
uint16_t get_dataset_code_by_name(const char* name);

class Dataset
{
public:
    static const uint16_t Invalid               =   0;
    static const uint16_t Elevation             =   1;
    static const uint16_t MinMaxElevation       =   2;
    static const uint16_t MaxCulture            =   3;
    static const uint16_t Imagery               =   4;
    static const uint16_t RMTexture             =   5;
    static const uint16_t RMDescriptor          =   6;
    static const uint16_t GSFeature             = 100;
    static const uint16_t GTFeature             = 101;
    static const uint16_t GeoPolitical          = 102;
    static const uint16_t VectorMaterial        = 200;
    static const uint16_t RoadNetwork           = 201;
    static const uint16_t RailRoadNetwork       = 202;
    static const uint16_t PowerLineNetwor       = 203;
    static const uint16_t HydrographyNetwork    = 204;
    static const uint16_t GSModelGeometry       = 300;
    static const uint16_t GSModelTexture        = 301;
    static const uint16_t GSModelSignature      = 302;
    static const uint16_t GSModelDescriptor     = 303;
    static const uint16_t NavData               = 400;
    static const uint16_t Navigation            = 401;
    static const uint16_t GTModelGeometry       = 500;
    static const uint16_t GTModelTexture        = 501;
    static const uint16_t GTModelSignature      = 502;
    static const uint16_t GTModelDescriptor     = 503;
    static const uint16_t MModelGeometry        = 600;
    static const uint16_t MModelTexture         = 601;
    static const uint16_t MModelSignature       = 602;
    static const uint16_t MModelDescriptor      = 603;

    Dataset(void);
    Dataset(uint16_t code);
    Dataset(const char* name);

    uint16_t code(void) const;
    const char* name(void) const;
    std::string subdir(void) const;

private:
    uint16_t _code;
};




} }
