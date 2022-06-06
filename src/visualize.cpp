#include "visualize.hpp"
#include "projections.hpp"
#include "libbmp/libbmp.h"

#include <iostream>
#include <cmath>

void drawRegions(const std::vector<Region>& regions)
{
    int mrate = 1000;
    Point limit = gallProjection(90, 180);
    int sizex = ceil(limit.x * mrate);
    int sizey = ceil(limit.y * mrate);
    std::cout << sizex << " " << sizey << std::endl;
    BmpImg img (sizex, sizey);
	for (int ix = 0; ix < sizex; ix++)
	{
		for (int iy = 0; iy < sizey; iy++)
		{
			img.set_pixel(ix, iy, 255, 255, 255);
		}
	}
    for (auto & region : regions)
    {
        for (auto & polygon : region.polygons)
        {
            for (int i = 0; i < polygon.size(); i++)
            {
                int sx = floor(polygon[i].x * mrate);
                int sy = floor(polygon[i].y * mrate);
                int fx = floor(polygon[(i + 1) % polygon.size()].x * mrate);
                int fy = floor(polygon[(i + 1) % polygon.size()].y * mrate);
                int len = fmax(abs(fx - sx), abs(fy - sy)) + 1;
                for (int j = 0; j <= len; j++)
                {
                    img.set_pixel(floor(sx + (fx - sx) * j / len), sizey - 1 - (sy + (fy - sy) * j / len), 0, 0, 0);
                }
            }
        }
    }

	img.write("test.bmp");
}