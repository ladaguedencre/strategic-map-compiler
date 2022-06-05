#include <iostream>

#include "parser.hpp"

int main()
{
    std::vector<Region> regions;
    parseGeoJson("./data/ne_10m.json", regions);
    std::cout << "kek" << std::endl;
}