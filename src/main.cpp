#include <iostream>

#include "parser.hpp"
#include "visualize.hpp"

int main()
{
    std::vector<Region> regions;
    parseGeoJson("./data/ne_10m.json", regions);
    drawRegions(regions);
    std::cout << "kek" << std::endl;
}