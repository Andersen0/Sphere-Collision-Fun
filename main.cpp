#include "sphere.h"
#include "collisions_low-level.h"
#include <random>
#include <iostream>
#include <vector>

std::mt19937 generator;
unsigned int gen_max_num; // Unsigned int because we don't want a negative value on the integer
unsigned int gen_min_num; 
int random_seed = rand();
int size_box = 10;
std::vector <Sphere> spheres;

int square_dist(int sphere_1, int sphere_2){
   int radii[3];
   int cent_box = size_box / 2;

   radii[0] = spheres[sphere_1].coords[0] - spheres[sphere_2].coords[0]; // X-coordinate difference between two spheres
   radii[1] = spheres[sphere_1].coords[1] - spheres[sphere_2].coords[1]; // Y-coordinate difference between two spheres
   radii[2] = spheres[sphere_1].coords[2] - spheres[sphere_2].coords[2]; // Z-coordinate difference between two spheres

   for(int i = 0; i < 3; i++){
      if(radii[i] < -cent_box)
         radii[i] += size_box;
      
      else if(radii[i] > size_box)
         radii[i] -= size_box;
   }

   int dist = sqrt(radii[0]*radii[0] + radii[1]*radii[1] + radii[2]*radii[2]); // Square distance 

   return dist;
}

int check_overlap(int a){
   int num_spheres = spheres.size();
   for(int i = 0; i < num_spheres; i++)
   {
      if(i != a)
      {
         if(square_dist(i, a) < spheres[i].size + spheres[a].size)
            return 1;
      }
   }
   return 0;
}

double mc_dist(){
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

int main(){
   int N = 0; // N will be the number of spheres
   std::cin >> N;  // input number of spheres

   generator.seed(random_seed);
   gen_max_num = generator.max();
   gen_min_num = generator.min();
 
   /*
    * three arrays for x, y, z coordinates of the spheres;
    * for example, the y coordinate of sphere with index 4 will be coordy[4]
    */
  
   /*
    * read all the data from standard input
    */
   for(int i = 0; i < N; i++)
   {
      std::cin >> spheres[i].size >> spheres[i].coords[0] >> spheres[i].coords[1] >> spheres[i].coords[2];
   }
   
   // int num_collisions = count_overlaps(N, spheres);
   // std::cout << num_collisions << " collisions were found.\n";


   // Monte Carlo loop; mc_dist() uses the mt19937 random number generator to generate random distances
   int mc_iter = 100;
   int num_spheres = 20;
   double num_moves = 0;
   int rand_sphere;
   int sphereMoved;

   for(int i = 1; i <= mc_iter;i++) 
    {
        for(int j = 0;j < num_spheres;j++)
        {
            rand_sphere = (int) (mc_dist() * num_spheres);
            sphereMoved = move_sphere(rand_sphere);
            num_moves += sphereMoved;
        }
    }
   // int num_collisions = count_overlaps(N, spheres);
   // std::cout << num_moves << " number of spheres were moved.\n";
   // std::cout << num_collisions << " collisions were found.\n";
}
