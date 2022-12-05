/**
*
* @file sphere.cpp
*
* @brief Generator of spheres and defines the variables attached to them. 
*/

#include "sphere.hpp"

Sphere::Sphere(){} // Default constructor for the sphere

// This pointers are used here because we have a nonstatic member function

Sphere::Sphere(double x, double y, double z){ 
    this -> place_coord(x, y, z);
    return;
}


/**
*
* @brief functions.cpp
*
* @param x double value of the x-coordinate value attributed to the sphere that is created.
* @param y double value of the y-coordinate value attributed to the sphere that is created.
* @param z double value of the z-coordinate value attributed to the sphere that is created.
*
* @return void 
*/

void Sphere::place_coord(double x, double y, double z){
    this -> coords[0] = x;
    this -> coords[1] = y; 
    this -> coords[2] = z; 
    return;
} 