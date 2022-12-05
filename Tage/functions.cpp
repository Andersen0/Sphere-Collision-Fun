/**
*
* @file functions.cpp
*
* @brief This file contains most the functions that are run in the MC-loop. 
*/

#include "functions.hpp"
#include "sphere.hpp"
#include "func_var.hpp"
#include <iostream>
#include <random>
#include <vector>


/**
*
* @brief square_dist measures the distance between two spheres and returns this result. 
*
* @param sphere_1 int value belonging to the first sphere
* @param sphere_2 int value belonging to the second sphere
*
* @return dist double value which is the gap between sphere 1 and 2 in regards to their center. 
*/

double square_dist(int sphere_1, int sphere_2){
   double diff[3];
   double cent_box = size_box / 2;

   // Minimum image convention (MIC) 
   diff[0] = spheres[sphere_1].coords[0] - spheres[sphere_2].coords[0]; // X-coordinate difference between two spheres
   diff[1] = spheres[sphere_1].coords[1] - spheres[sphere_2].coords[1]; // Y-coordinate difference between two spheres
   diff[2] = spheres[sphere_1].coords[2] - spheres[sphere_2].coords[2]; // Z-coordinate difference between two spheres 

   for(int i = 0; i < 3; i++){
      if(diff[i] < -cent_box)
         diff[i] += size_box;
      
      else if(diff[i] > size_box)
         diff[i] -= size_box;
   }

   double dist = sqrt(diff[0]*diff[0] + diff[1]*diff[1] + diff[2]*diff[2]); // Square distance
   //std::cout << dist << " square distance" << std::endl; 

   return dist;
}


/**
*
* @brief sphere_PBC makes sure that the spheres don't move outside of the box.
*
* @param i is the int value belonging to the given sphere we are checking the boundary condition on. 
*
* @return void
*/

void sphere_PBC(int i) // This function creates a periodic boundary condition of the spheres
{
   double l_box = size_box / 2;
   for(int j = 0; j < 3; j++) // Iterating through the coordinates x, y and z
   {
      // Here we restrict the sphere coordinates to the simulated box
      if(spheres[i].coords[j] < -l_box+rad) 
         spheres[i].coords[j] += size_box-(2*rad);
      else if(spheres[i].coords[j] > l_box-rad) 
         spheres[i].coords[j] -= size_box-(2*rad);  
   }
   return;
}


/**
*
* @brief check_overlap iterates over all spheres except i and checks if the square_dist value is below the overlap thresholds. 
*
* @param i is the int value belonging to the sphere we are checking overlaps on. 
*
* @return bool value
*/

bool check_overlap(int i){
   // Checking for overlap between spheres
   int num_spheres = spheres.size(); // Using size() to get the total number of spheres
   for(int j = 0; j < num_spheres; j++) // Iterating through the number of spheres
   {
      overlap = 0;
      if(i != j)
      {
         //std::cout << i << std::endl;
         if (square_dist(i, j) < rad){
            //std::cout << i << " sphere returned 8" << std::endl;
            overlap = 8;
            return 1; // If the square distance of the two spheres is less than the sum of half the radii of the spheres, there is 8 collisions
         } 
         else if(square_dist(i, j) < 2*rad){
            //std::cout << i << " sphere returned 1" << std::endl;
            overlap = 1;
            return 1; // If the square distance of the two spheres is less than the sum of the radii of the spheres, there is a collision
         }
      }
   }
   return 0;
}


/**
*
* @brief mc_dist generates a random distance by taking the random number generated and dividing by the difference between the max and min
*
* @return double value 
*/

double mc_dist(){
   // It generates a random distance by taking the random number generated and dividing by the difference between the max and min
   // number that was generated and adding +1 to it
   // Static_cast is used here to convert one data type into another data type, here converted from int to double since
   // gen_max_num and gen_min_num is an unsigned int
   // Moreover, using double here instead of int or float makes it easier for the code to deal with decimal points
   return(static_cast<double>(generator()) / (static_cast<double> (gen_max_num - gen_min_num) + 1));
}


/**
*
* @brief move_sphere changes the coordinates of the spheres and checks for overlaps. If there is an overlap then the spheres are returned to the original coordinate. PBC is also tested. 
*
* @param a is the int value belonging to the sphere we are potentially moving.
*
* @return int value which is counted for number of moves later.
*/

int move_sphere(int a){
   double mc_x; double mc_y; double mc_z;
   double prev_x; double prev_y; double prev_z;

   // Randomly generated distance
   mc_x = mc_dist() + rad;
   mc_y = mc_dist() + rad;
   mc_z = mc_dist() + rad;
   // Previous positions of coordinates x, y and z
   prev_x = spheres[a].coords[0];
   prev_y = spheres[a].coords[1];
   prev_z = spheres[a].coords[2];

   // Establishes a new distance based on the previous position and and mc_dist()
   spheres[a].coords[0] = prev_x + mc_x;
   spheres[a].coords[1] = prev_y + mc_y;
   spheres[a].coords[2] = prev_z + mc_z;

   //std::cout << spheres[a].coords[0] << " " << spheres[a].coords[1] << " " << spheres[a].coords[2] << " old " << std::endl;
   sphere_PBC(a); // Periodic boundary condition
   //std::cout << spheres[a].coords[0] << " " << spheres[a].coords[1] << " " << spheres[a].coords[2] << " new " << std::endl;


   if(check_overlap(a))
   {
      // If there is an overlap between the spheres in the new position, move the sphere back to the previous position
      spheres[a].coords[0] = prev_x;
      spheres[a].coords[1] = prev_y;
      spheres[a].coords[2] = prev_z;
   
      return 0;
   } 
   return 1;
}
