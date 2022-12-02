#include "sphere.hpp"

Sphere::Sphere(){} // Default constructor for the sphere

// This pointers are used here because we have a nonstatic member function

Sphere::Sphere(double x, double y, double z){ 
    this -> place_coord(x, y, z);
    return;
}

void Sphere::place_coord(double x, double y, double z){
    this -> coords[0] = x;
    this -> coords[1] = y; 
    this -> coords[2] = z; 
    return;
} 