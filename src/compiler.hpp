#pragma once

#include "region.hpp"

#include <vector>

struct JointPoint
{
public:
    Point point;
    std::vector<int> regions;
};

class MapCompiler
{
public:
    MapCompiler(const std::vector<Region>& regions);
    void clusterizeRegions();

private:
    void extractJointPoints();
    void insertJointPoint(Point point, int regIndex);

private:
    std::vector<JointPoint> pointsGrid_[240][396];
    const std::vector<Region>& regions_;
};