#include "collisions_low-level.h"

// is there a collision between sphere i and sphere j?
//
// by a collision here we mean a genuine overlap between spheres:
// if two spheres barely touch each other (square_distance == sum_of_radii*sum_of_radii) it does not count as a collision;
//
// it is only counted if, below, the square distance is properly smaller than the square of the sum of radii
//

bool check_collision(
   float size_i,   float size_j,    /* note: "size" is here the sphere diameter, for i and j, respectively */
   float coordx_i, float coordx_j,
   float coordy_i, float coordy_j,
   float coordz_i, float coordz_j
) {
   /*
    * vector pointing from the centre of i to the centre of j
    */
   float distancex = coordx_j - coordx_i;
   float distancey = coordy_j - coordy_i;
   float distancez = coordz_j - coordz_i;
   
   /*
    * square of that vector
    */
   float square_distance = distancex*distancex + distancey*distancey + distancez*distancez;
   
   /*
    * is the square distance smaller than the square of the sum of radii?
    */
   float sum_of_radii = 0.5*(size_i+size_j);
   return square_distance < sum_of_radii*sum_of_radii;
}

// count the number of collisions between pairs of spheres
//
