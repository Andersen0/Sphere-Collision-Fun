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
int num_spheres = 14000; // A pre-set total number of spheres
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
    std::cout << "=======================\n";
    std::cout << num_moves << " moves were made.\n"; 
    std::cout << num_overlaps << " overlaps were found at the end of the MC-loop."; 
    auto t1 = std::chrono::high_resolution_clock::now(); // End-time
    auto delta_t01 = std::chrono::duration_cast<std::chrono::microseconds>(t1-t0).count(); // Total runtime
    std::cout << "\nOverall runtime: "  << 1.0e-06*(delta_t01) << " s\n";
}
