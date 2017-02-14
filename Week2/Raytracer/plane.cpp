
#include "plane.h"
#include <iostream>
#include <math.h>

/************************** Sphere **********************************/

Hit Plane::intersect(const Ray &ray)
{
	//GIVEN : ray.D, ray.O, normal, d
	
	double t = (-((ray.O).dot(normal) + d)) / (ray.D.dot(normal));
	
    return Hit(t,normal);
}

