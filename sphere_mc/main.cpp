#include "sphere.hpp"
#include "functions.hpp"
#include <random>
#include <iostream>
#include <vector>

std::minstd_rand generator; // Pseudo-random number generator 
unsigned int gen_max_num; // Unsigned int because we don't want a negative value on the integer
unsigned int gen_min_num; 
int rand_seed = rand();
int size_box = 10;
int rad = 1;
std::vector <Sphere> spheres;
int mc_iter = 100;
int num_spheres = 20;
double num_moves = 0;
int rand_sphere;
int sphereMoved;
int num_collisions;

int main(){

   generator.seed(rand_seed);
   gen_max_num = generator.max();
   gen_min_num = generator.min();

   // Monte Carlo loop; mc_dist() uses the minstd_rand random number generator to generate random distances
   for(int i = 1; i <= mc_iter;i++) // Iterating through a pre-set number of Monte Carlo iterations
    {
        for(int j = 0; j < num_spheres; j++) // Iterating through a pre-set number of spheres
        {
            rand_sphere = int(mc_dist() * num_spheres); // Using int() here because mc_dist() is a double and num_spheres is a int
            sphereMoved = move_sphere(rand_sphere); // A sphere is moved if the move_sphere function is true
            num_moves += sphereMoved; // Adding to the total number of moves 
            if(check_overlap(j)){
                num_collisions++;
            }
        }
    }
    std::cout << num_moves << " number of spheres were moved.\n";
    std::cout << num_collisions << " collisions were found.\n";
}