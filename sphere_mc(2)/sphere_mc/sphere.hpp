#ifndef __SPHERE__
#define __SPHERE__

struct Sphere{
    Sphere();
    double coords[3];
    Sphere(double, double, double);
    void place_coord(double, double, double);
};

#endif