#include "projections.hpp"

#include <cmath>

Point gallProjection(float lat, float lon)
{
    float x = (lon + 180) / sqrt(2) / 50.0;
    float latRad = lat * M_PI/180;
    float y = (1 + sqrt(0.5))*(tan(latRad / 2) + 1);
    return Point{x, y};
}