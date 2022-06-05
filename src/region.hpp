#pragma once

#include <vector>
#include <string>

struct Point
{
    float lat;
    float lon;
};

typedef std::vector<std::vector<Point>> Polygons;

struct Region
{
    Polygons polygons;
    std::string name;
    std::string nameUkr;
    std::string unit;
    size_t id;
};