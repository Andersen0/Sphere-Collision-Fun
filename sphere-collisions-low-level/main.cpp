#include <iostream>
#include "collisions_low-level.h"

struct Sphere {
   float size = 0.0;
   float coords[3] = {0.0, 0.0, 0.0};
};

int count_collisions(int N, Sphere* spheres)
{
   int num_collisions = 0;
   
   /*
    * loop going from i = 0, j = 1 up to i = N-2, j = N-1, traversing all pairs
    */
   for(int i = 0; i < N-1; i++)
      for(int j = i+1; j < N; j++)
         if(check_collision(spheres[i].size, spheres[j].size, 
         spheres[i].coords[0], spheres[j].coords[0], spheres[i].coords[1], 
         spheres[j].coords[1], spheres[i].coords[2], spheres[j].coords[2]))
            num_collisions++;
   
   return num_collisions;
}


int main()
{
   int N = 0; // N will be the number of spheres
   std::cin >> N;  // input number of spheres
   Sphere* spheres = new Sphere[N]();
 
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
   
   /*
    * how many collisions are there between the spheres?
    * 
    * note: collision here means "overlap" between spheres
    */
   int num_collisions = count_collisions(N, spheres);
   std::cout << num_collisions << " collisions were found.\n";
   
   /*
    * deallocate all the arrays created with "new"
    */
 
}

