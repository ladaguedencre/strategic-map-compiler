#pragma once

#include <vector>
#include <string>

struct Point
{
    float x;
    float y;

    bool coincides(const Point& other)
    {
        // TODO: implement better comparison
        return abs(x - other.x) + abs(y - other.y) < 0.001;
    }
};

typedef std::vector<Point> Polygon;
typedef std::vector<Polygon> Polygons;

struct Region
{
    Polygons polygons;
    std::string name;
    std::string nameUkr;
    std::string unit;
    size_t id;
};