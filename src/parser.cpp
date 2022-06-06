#include "parser.hpp"
#include "projections.hpp"
#include "nlohmann/json.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

using json = nlohmann::json;

namespace {

    bool parsePolygon(json polygonJson, Polygon& polygon)
    {
        auto innerArray = polygonJson[0];
        if (!innerArray.is_array())
        {
            return false;
        }
        for (json::iterator it = innerArray.begin(); it != innerArray.end(); it++)
        {
            if (!(*it).is_array() || (*it).size() != 2 || !(*it)[0].is_number() || !(*it)[1].is_number())
            {
                return false;
            }
            float lat = (*it)[1].get<float>();
            float lon = (*it)[1].get<float>();
            if (lat < -90 || lat > 90 || lon < -180 || lon > 180)
            {
                return false;
            }
            Point point = gallProjection((*it)[1].get<float>(), (*it)[0].get<float>());
            if (isnan(point.x) || isnan(point.y))
            {
                return false;
            }
            polygon.push_back(point);
        }
        return true;
    }

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
            Polygon polygon;
            if (!parsePolygon(coordsJson, polygon))
            {
                return false;
            }
            region.polygons.push_back(polygon);
        }
        else
        {
            for (json::iterator it = coordsJson.begin(); it != coordsJson.end(); it++)
            {
                Polygon polygon;
                if (!parsePolygon((*it), polygon))
                {
                    continue;
                }
                region.polygons.push_back(polygon);
            }
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


