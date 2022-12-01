#include "sphere.hpp"
#include "functions.hpp"
#include <random>
#include <iostream>
#include <vector>

std::minstd_rand generator; // Pseudo-random number generator 
unsigned int gen_max_num; // Unsigned int because we don't want a negative value on the integer
unsigned int gen_min_num; 
int rand_seed = 1219;
int size_box = 20;
int rad = 1;
std::vector <Sphere> spheres;
int num_moves;
int rand_sphere;
int sphereMoved;
int mc_iter = 100;
int num_spheres = 100;
int num_overlaps;

int main(){
    generator.seed(rand_seed); // Generating random numbers from a randomly given seed
    gen_max_num = generator.max(); // Returning the maximum number from the randomly generated number
    gen_min_num = generator.min(); // Returning the minimum number from the randomly generated number

    // Placing the spheres 
    for(int i = 0; i < num_spheres; i++){
        double placed_x; double placed_y; double placed_z;

        placed_x = (mc_dist() * size_box) - size_box / 2;
        placed_y = (mc_dist() * size_box) - size_box / 2;
        placed_z = (mc_dist() * size_box) - size_box / 2;
        
        Sphere sphere;
        sphere.place_coord(placed_x, placed_y, placed_z);

        spheres.push_back(sphere); // Adds a new element, in this case a sphere with set coordinates to the end of a vector
                                   // equivalent to .append() in Python
    }

    // Monte Carlo loop; mc_dist() uses the minstd_rand random number generator to generate random distances
    for(int i = 1; i <= mc_iter; i++){ // Iterating through a pre-set number of Monte Carlo iterations
        for(int j = 0; j < num_spheres; j++) // Iterating through a pre-set number of spheres
        {
            rand_sphere = int(mc_dist() * num_spheres); // Using int() here because mc_dist() is a double and num_spheres is a int
            sphereMoved = move_sphere(rand_sphere); // A sphere is moved if the move_sphere function is true
            num_moves += sphereMoved; // Adding to the total number of moves 
            if(check_overlap(j)){
                num_overlaps++;
            }
        }
        std::cout << num_overlaps << " overlaps were found.\n";
    }
    std::cout << num_moves << " number of spheres were moved.\n";
    std::cout << num_overlaps << " overlaps were found.\n"; 
}
