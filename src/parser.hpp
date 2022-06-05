#pragma once

#include "region.hpp"

#include <string>
#include <vector>

bool parseGeoJson(std::string filename, std::vector<Region>& regions);