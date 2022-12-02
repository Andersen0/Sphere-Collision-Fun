#ifndef __FUNC_VAR__
#define __FUNC_VAR__

#include "sphere.hpp"
#include <random>

// The extern keyword is used here on global variables to specify that the variables have an external linkage

extern std::minstd_rand generator;
extern unsigned int gen_max_num;
extern unsigned int gen_min_num;
extern int num_spheres;
extern int rand_seed;
extern int mc_iter;
extern double rad;
extern double size_box;
extern std::vector <Sphere> spheres;

#endif 