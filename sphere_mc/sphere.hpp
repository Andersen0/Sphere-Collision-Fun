#ifndef __SPHERE__
#define __SPHERE__

struct Sphere{
    double coords[3];
    Sphere(double, double, double);
    void det_coord(double, double, double);
};

#endif