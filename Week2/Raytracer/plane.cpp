
#include "plane.h"
#include <iostream>
#include <math.h>

/************************** Sphere **********************************/

Hit Plane::intersect(const Ray &ray)
{
	//GIVEN : ray.D, ray.O, normal, d
	
	double t = (-(ray.O).dot(normal)) / (ray.D.dot(normal));
	
    return Hit(t,normal);
}

