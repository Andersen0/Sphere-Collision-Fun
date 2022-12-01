#include "functions.hpp"
#include "sphere.hpp"
#include "func_var.hpp"
#include <iostream>
#include <random>
#include <vector>

double square_dist(int sphere_1, int sphere_2){
   int diff[3];
   int cent_box = size_box / 2;

   diff[0] = spheres[sphere_1].coords[0] - spheres[sphere_2].coords[0]; // X-coordinate difference between two spheres
   diff[1] = spheres[sphere_1].coords[1] - spheres[sphere_2].coords[1]; // Y-coordinate difference between two spheres
   diff[2] = spheres[sphere_1].coords[2] - spheres[sphere_2].coords[2]; // Z-coordinate difference between two spheres

   for(int i = 0; i < 3; i++){
      if(diff[i] < -cent_box)
         diff[i] += size_box;
      
      else if(diff[i] > size_box)
         diff[i] -= size_box;
   }

   int dist = sqrt(diff[0]*diff[0] + diff[1]*diff[1] + diff[2]*diff[2]); // Square distance 

   return dist;
}

void sphere_PBC(int i)
{
    double cent_box = size_box / 2;
    for(int j = 0; j < 3; j++)
    {
        if(spheres[i].coords[j] < -cent_box)
            spheres[i].coords[j] += size_box;
        else if(spheres[i].coords[j] > cent_box)
            spheres[i].coords[j] -= size_box; 
    }
    return;
}

int check_overlap(int i){
   // Checking for overlap between spheres
   int num_spheres = spheres.size(); // Using size() to get the total number of spheres
   for(int j = 0; j < num_spheres; j++) // Iterating through the number of spheres
   {
      if(i != j) 
      {
         // If the square distance of the two spheres is less than the diameter of the spheres, there is a collision
         if(square_dist(i, j) < 2*rad)
            return 1;
      }
   }
   return 0;
}

double mc_dist(){
   // It generates a random distance by taking the random number generated and dividing by the difference between the max and min
   // number that was generated and adding +1 to it
   // Static_cast is used here to convert one data type into another data type, here converted from int to double
   return(static_cast<double>(generator()) / (static_cast<double> (gen_max_num - gen_min_num) + 1.0));
}

int move_sphere(int a){
   double mc_x; double mc_y; double mc_z;
   double prev_x; double prev_y; double prev_z;

   // Choosing small numbers here to make the moving distance small
   mc_x = (mc_dist() - 0.3) * 0.3;
   mc_y = (mc_dist() - 0.3) * 0.3;
   mc_z = (mc_dist() - 0.3) * 0.3;

   // Previous positions
   prev_x = spheres[a].coords[0];
   prev_y = spheres[a].coords[1];
   prev_z = spheres[a].coords[2];

   // Adds the distance to the previous position with the Monte Carlo random number generator mc_dist()
   spheres[a].coords[0] = prev_x + mc_x;
   spheres[a].coords[1] = prev_y + mc_y;
   spheres[a].coords[2] = prev_z + mc_z;

   sphere_PBC(a);

   if(check_overlap(a))
   {
      // If there is an overlap/collision between spheres, move the sphere back to the previous position
      spheres[a].coords[0] = prev_x;
      spheres[a].coords[1] = prev_y;
      spheres[a].coords[2] = prev_z;
      return 0;
   } 
   return 1;
}
