#include "collisions_low-level.h"
#include "collisions_low-level.o"
#include <stdlib.h>  
#include "main.cpp"


void wrapPBC(Sphere* spheres)
{
    double box_size = 20;
    double box_lim = box_size / 2.0;
    for(int j = 0;j < 3; j++)
    {
        if(spheres[i].coords[j] > box_lim )
            spheres[i].coords[j] -= box_size;
        else if(spheres[i].coords[j] < -box_lim)
            spheres[i].coords[j] += box_size;
    }
    return;
}

double udist()
{
    return (static_cast<double>(generator()) / (static_cast<double> (GEN_MAX - GEN_MIN) + 1.0));
}

int moveSphere(int i, Sphere* spheres)
{
    double dx, dy, dz;
    double oldx, oldy, oldz;

    dx = (udist() - 0.5) * 0.2;
    dy = (udist() - 0.5) * 0.2;
    dz = (udist() - 0.5) * 0.2;

    oldx = spheres[i].coords[0];
    oldy = spheres[i].coords[1];
    oldz = spheres[i].coords[2];

    spheres[i].coords[0] = oldx + dx;
    spheres[i].coords[1] = oldy + dy;
    spheres[i].coords[2] = oldz + dz;

    wrapPBC(i);

    if(check_collision(i))
    {
        spheres[i].coords[0] = oldx;
        spheres[i].coords[1] = oldy;
        spheres[i].coords[2] = oldz;
        return 0;
    }
    return 1;
}
