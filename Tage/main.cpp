/**
*
* @file main.cpp
* @author Tage Andersen, Elias Evjen Hartmark, Marko Miric
* @brief Main contains important parameters and the MC-loop plus initialization of the sphere generation and random seed. 
*
* @version 1
* @date 2022-12-5
* @copyright Copyright (c) 2022
*/

/*! \mainpage INF205: Resource-efficient programming (2022H)
 *
 * \section  Assignment
 *
 * Topic: Sphere overlap
Summary

There are a n spheres, for each of which the diameter and the coordinate of the centre is given as part of the input. Your code should, as a first functionality (which already existed in code from the lecture), be able to efficiently compute the number of overlaps. As a second functionality, the code should be able to rearrange the spheres, confined within a finite volume, in order to reduce the number of overlaps. In particular, where possible, a configuration completely without overlaps should be generated.
Default recommendations

Use a cube-shaped box (containing the spheres) with periodic boundary conditions and the minimum image convention.

You can deviate from the default recommendations; follow them if you do not see any good reason not to.
Benchmark scenario

The benchmark scenario has one main parameter, the number of particles N. It can be generated using the sphere benchmark scenario generator. The size value contained in the scenario generator output is the sphere diameter, not the sphere radius.

Optionally, additional parameters can be varied in the benchmark scenario: The packing fraction (default: ξ = 7/9) and the size ratio between the largest and smallest spheres (default: ζmax = 10/3).
Technical remarks

If the centres of two spheres are closer than the sum of their radii, it should be counted as one overlap, except if they are closer than half the sum of their radii: Then this should count with a factor eight, i.e., as equivalent to eight overlaps.

It will often be hard to find the exact global minimum of the number of overlaps for large values of n; in these cases the aim is to find a good approximation.
Why is this an interesting topic?

Hard spheres are in use as a simple model for simulation of condensed phases (solids and liquids) and of granular media (materials such as sand). They are a good system for getting started with methodology, algorithms, and data structures that are in use for particle-based simulations, which is a major field of use for scientific high performance computing infrastructures, and useful for many engineering applications.
 *
 * \section Authors
 * Marko Miric, Elias Evjen Hartmark and Tage Andersen from group 12. 
 * 
 *
 * 
 */

#include "sphere.hpp"
#include "functions.hpp"
#include "func_var.hpp"
//#include "matplotlibcpp.h"
//namespace plt = matplotlibcpp;
#include <random>
#include <iostream>
#include <vector>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>  



std::minstd_rand generator; // Pseudo-random number generator 
unsigned int gen_max_num; // Unsigned int because we don't want a negative value on the integer
unsigned int gen_min_num; 
int rand_seed = rand()%100;
double size_box = 50; // A pre-set size of the box
double rad = 1; // A pre-set radius of a sphere
std::vector <Sphere> spheres;
int num_moves;
int overlap;
int rand_sphere; 
int sphereMoved;
int mc_iter = 2000; // A pre-set maximum number of total number of iterations in the Monte Carlo loop
int num_spheres = 1000; // A pre-set total number of spheres
int num_overlaps;


int main(){
    auto t0 = std::chrono::high_resolution_clock::now(); // Start-time

    srand(time(NULL));
    generator.seed(rand()%100); // Generating random numbers from a randomly given seed

    gen_max_num = generator.max(); // Returning the maximum number from the randomly generated number
    gen_min_num = generator.min(); // Returning the minimum number from the randomly generated number

    // Placing the spheres 
    for(int i = 0; i < num_spheres; i++){
        double placed_x; double placed_y; double placed_z;

        placed_x = (mc_dist() * (size_box)) - (size_box / 2); // Set x-coordinate that is dependent on mc_dist() which is random
        placed_y = (mc_dist() * (size_box)) - (size_box / 2); // Set y-coordinate that is dependent on mc_dist() which is random
        placed_z = (mc_dist() * (size_box)) - (size_box / 2); // Set z-coordinate that is dependent on mc_dist() which is random
        
        Sphere sphere;
        sphere.place_coord(placed_x, placed_y, placed_z); // Placing the coordinates in the box

        spheres.push_back(sphere); // Adds a new element, in this case a sphere with set coordinates to the end of a vector
                                   // equivalent to .append() in Python
    }
    
    // Monte Carlo loop; mc_dist() uses the minstd_rand random number generator to generate random distances
    for(int i = 1; i <= mc_iter; i++){ // Iterating through a pre-set number of Monte Carlo iterations
        num_overlaps = 0;
        for(int c = 0; c < num_spheres; c++){
            if (check_overlap(c))
            {
                num_overlaps += overlap;
            }
        }
        for(int j = 0; j < num_spheres; j++){ // Iterating through a pre-set number of spheres
                rand_sphere = int(mc_dist() * num_spheres); // Using int() here because mc_dist() is a double and num_spheres is a int
                sphereMoved = move_sphere(rand_sphere); // A sphere is moved if the move_sphere function is true
                num_moves += sphereMoved; // Adding to the total number of moves
                //std::cout << num_overlaps << " overlaps." << std::endl;
            }
        std::cout << num_overlaps << " overlaps were found.\n"; // Printing number of overlaps after every MC-iteration
        if (num_overlaps == 0) {
            std::cout << i << " number of MC iterations were performed." << std::endl;
            break;
        }
    }
    
    int p = 0;
    std::ofstream outfile ("test.txt");

    outfile << size_box << std::endl;
    outfile << num_spheres << std::endl;
    for (p=0; p<num_spheres; p++){
        outfile << spheres[p].coords[0] << " " << spheres[p].coords[1] << " " << spheres[p].coords[2] << std::endl;
    }

    outfile.close();

    std::cout << "=======================\n";
    std::cout << num_moves << " moves were made.\n"; 
    std::cout << num_overlaps << " overlaps were found at the end of the MC-loop."; 
    auto t1 = std::chrono::high_resolution_clock::now(); // End-time
    auto delta_t01 = std::chrono::duration_cast<std::chrono::microseconds>(t1-t0).count(); // Total runtime
    std::cout << "\nOverall runtime: "  << 1.0e-06*(delta_t01) << " s\n";
}
