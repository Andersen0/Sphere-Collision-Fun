#include "sphere.hpp"

Sphere::Sphere(double x, double y, double z){
    this -> det_coord(x, y, z);
    return;
}

void Sphere::det_coord(double x, double y, double z){
    this -> coords[0] = x;
    this -> coords[1] = y;
    this -> coords[2] = z;
    return;
} 