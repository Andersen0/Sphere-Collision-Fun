#ifndef sphere.h
#define sphere.h

struct Sphere{
    double coords[3];
    Sphere(double, double, double);
    void det_coord(double, double, double);
    double size = 0.0;
};

#endif