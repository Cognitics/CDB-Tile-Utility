
#include "Dataset.h"

#include <sstream>
#include <iomanip>

////////////////////////////////////////////////////////////////////////////////
// local

namespace {

struct Local
{
    std::map<int, const char*> dataset_name_by_code;
    std::map<const char*, int> dataset_code_by_name;

    void init_dataset_name_by_code(void)
    {
        dataset_name_by_code[1] = "Elevation";
        dataset_name_by_code[2] = "MinMaxElevation";
        dataset_name_by_code[3] = "MaxCulture";
        dataset_name_by_code[4] = "Imagery";
        dataset_name_by_code[5] = "RMTexture";
        dataset_name_by_code[6] = "RMDescriptor";
        dataset_name_by_code[100] = "GSFeature";
        dataset_name_by_code[101] = "GTFeature";
        dataset_name_by_code[102] = "GeoPolitical";
        dataset_name_by_code[200] = "VectorMaterial";
        dataset_name_by_code[201] = "RoadNetwork";
        dataset_name_by_code[202] = "RailRoadNetwork";
        dataset_name_by_code[203] = "PowerLineNetwork";
        dataset_name_by_code[204] = "HydrographyNetwork";
        dataset_name_by_code[300] = "GSModelGeometry";
        dataset_name_by_code[301] = "GSModelTexture";
        dataset_name_by_code[302] = "GSModelSignature";
        dataset_name_by_code[303] = "GSModelDescriptor";
        dataset_name_by_code[400] = "NavData";
        dataset_name_by_code[401] = "Navigation";
        dataset_name_by_code[500] = "GTModelGeometry";
        dataset_name_by_code[501] = "GTModelTexture";
        dataset_name_by_code[502] = "GTModelSignature";
        dataset_name_by_code[503] = "GTModelDescriptor";
        dataset_name_by_code[600] = "MModelGeometry";
        dataset_name_by_code[601] = "MModelTexture";
        dataset_name_by_code[602] = "MModelSignature";
        dataset_name_by_code[603] = "MModelDescriptor";
    }

    void init_dataset_code_by_name(void)
    {
        for(std::map<int, const char*>::iterator it = dataset_name_by_code.begin(), end = dataset_name_by_code.end(); it != end; ++it)
            dataset_code_by_name[it->second] = it->first;
    }

    Local(void)
    {
        init_dataset_name_by_code();
        init_dataset_code_by_name();
    }

    const char* get_dataset_name_by_code(uint16_t code)
    {
        std::map<int, const char*>::iterator it = dataset_name_by_code.find(code);
        return (it == dataset_name_by_code.end()) ? "Invalid" : it->second;
    }

    uint16_t get_dataset_code_by_name(const char* name)
    {
        std::map<const char*, int>::iterator it = dataset_code_by_name.find(name);
        return (it == dataset_code_by_name.end()) ? 0 : it->second;
    }


} local;

}

////////////////////////////////////////////////////////////////////////////////
// util

namespace cognitics {
namespace cdb {

std::map<int, const char*> get_datasets_map_by_code(void)
{
    return local.dataset_name_by_code;
}

std::map<const char*, int> get_datasets_map_by_name(void)
{
    return local.dataset_code_by_name;
}

const char* get_dataset_name_by_code(uint16_t code)
{
    return local.get_dataset_name_by_code(code);
}

uint16_t get_dataset_code_by_name(const char* name)
{
    return local.get_dataset_code_by_name(name);
}

} }

////////////////////////////////////////////////////////////////////////////////
// Dataset

namespace cognitics {
namespace cdb {

Dataset::Dataset(void) : _code(0)
{
}

Dataset::Dataset(uint16_t code) : _code(code)
{
}

Dataset::Dataset(const char* name) : _code(0)
{
}

uint16_t Dataset::code(void) const
{
    return _code;
}

const char* Dataset::name(void) const
{
    return get_dataset_name_by_code(_code);
}

std::string Dataset::subdir(void) const
{
    std::stringstream ss;
    ss << std::setw(3) << std::setfill('0') << _code;
    ss << "_" << get_dataset_name_by_code(_code);
    return ss.str();
}


} }
