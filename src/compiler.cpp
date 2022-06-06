#include "compiler.hpp"

#include <cmath>

double area(Polygon polygon)
{
    // Works only for convex polygons
    double area = 0.0;
    for (int i = 0; i < polygon.size(); i++)
    {
        area += (polygon[i].x + polygon[(i + 1) % polygon.size()].x) * (polygon[i].y - polygon[(i + 1) % polygon.size()].y);
    }
    return abs(area / 2.0);
}

void MapCompiler::insertJointPoint(Point point, int regIndex)
{
    int ix = floor(point.x);
    int iy = floor(point.y);
    for (int i1 = 0; i1 < pointsGrid_[ix][iy].size(); i1++)
    {
        if (point.coincides(pointsGrid_[ix][iy][i1].point))
        {
            pointsGrid_[ix][iy][i1].regions.push_back(regIndex);
            return;
        }
    }
    pointsGrid_[ix][iy].push_back(JointPoint{point, {regIndex}});
}

void MapCompiler::extractJointPoints()
{
    for (int i1 = 0; i1 < regions_.size(); i1++)
    {
        for (auto& coord : regions_[i1].polygons[0])
        {
            insertJointPoint(coord, i1);
        }
    }
}

MapCompiler::MapCompiler(const std::vector<Region>& regions)
    : regions_(regions)
{
    extractJointPoints();
}

void MapCompiler::clusterizeRegions()
{
    // TODO: clusterize
}