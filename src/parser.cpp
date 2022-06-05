#include "parser.hpp"
#include "nlohmann/json.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

using json = nlohmann::json;

namespace {
    bool parseGeometry(json geometryJson, Region& region)
    {
        if (!geometryJson.is_object())
        {
            return false;
        }
        auto typeJson = geometryJson["type"];
        auto coordsJson = geometryJson["coordinates"];
        if (!typeJson.is_string() || !coordsJson.is_array())
        {
            return false;
        }
        std::string type = typeJson.get<std::string>();
        if (type == "Polygon")
        {
            auto innerArray = coordsJson[0];
            if (!innerArray.is_array())
            {
                return false;
            }
            std::vector<Point> vp;
            for (json::iterator it = innerArray.begin(); it != innerArray.end(); it++)
            {
                if (!(*it).is_array() || (*it).size() != 2 || !(*it)[0].is_number() || !(*it)[1].is_number())
                {
                    return false;
                }
                vp.push_back(Point{(*it)[0].get<float>(), (*it)[1].get<float>()});
            }
            region.polygons.push_back(vp);
        }
        else
        {
            // TODO: parse multipolygon
            return false;
        }
        
        return true;
    }

    bool parseProperties(json propertiesJson, Region& region)
    {
        auto nameJson = propertiesJson["name"];
        auto unitJson = propertiesJson["geonunit"];
        auto nameUkrJson = propertiesJson["name_uk"];
        auto idJson = propertiesJson["gn_id"];
        if (!nameJson.is_string() || !unitJson.is_string() || !unitJson.is_string() || !idJson.is_number())
        {
            return false;
        }
        region.name = nameJson.get<std::string>();
        region.unit = unitJson.get<std::string>();
        region.nameUkr = nameUkrJson.get<std::string>();
        region.id = idJson.get<size_t>();
        return true;
    }
}

bool parseGeoJson(std::string filename, std::vector<Region>& regions)
{
    std::ifstream fin(filename);
    if (!fin)
    {
        std::cout << "Unable to read file" << std::endl;
        return false;
    }
    std::stringstream sbuf;
    sbuf << fin.rdbuf();
    auto fullJson = json::parse(sbuf);
    auto featuresJson = fullJson["features"];
    if (!featuresJson.is_array())
    {
        std::cout << "Invalid data format" << std::endl;
        return false;
    }
    for (json::iterator it = featuresJson.begin(); it != featuresJson.end(); it++)
    {
        Region region;
        if (!parseGeometry((*it)["geometry"], region) || !parseProperties((*it)["properties"], region))
        {
            continue;
        }
        regions.push_back(region);
        std::cout << regions.size() << std::endl;
    }
    return true;
}


