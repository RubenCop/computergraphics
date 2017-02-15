//
//  Framework for a raytracer
//  File: sphere.cpp
//
//  Created for the Computer Science course "Introduction Computer Graphics"
//  taught at the University of Groningen by Tobias Isenberg.
//
//  Authors:
//    Maarten Everts
//    Jasper van de Gronde
//
//  This framework is inspired by and uses code of the raytracer framework of
//  Bert Freudenberg that can be found at
//  http://isgwww.cs.uni-magdeburg.de/graphik/lehre/cg2/projekt/rtprojekt.html
//

#include "torus.h"
#include <iostream>
#include <math.h>

/************************** Sphere **********************************/

Hit Torus::intersect(const Ray &ray)
{
  //Given: pos, r1, r2, ray.O, ray.D
  double x = position.data[0];
  double y = position.data[1];
  double z = position.data[2];

  cout << x << endl;


}
