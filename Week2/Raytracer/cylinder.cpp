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

#include "cylinder.h"
#include <iostream>
#include <math.h>

/************************** Sphere **********************************/

Hit Cylinder::intersect(const Ray &ray)
{
    //Direction vector of cylinder
    Triple dirVec = p2 - p1;

    //Temporary variables for clarity
    Triple t1 = ray.D - (ray.D.dot(dirVec)/dirVec.dot(dirVec)) * dirVec;
    Triple t2 = (ray.O - p1) - ((ray.O - p1).dot(dirVec)/dirVec.dot(dirVec)) * dirVec;

    double a = t1.dot(t1);
    double b = 2 * t1.dot(t2);
    double c = t2.dot(t2) - r * r;

	double t = 0;

	double d = b * b - 4 * a * c;

	if (d < 0) //No solutions, so no hit
		return Hit::NO_HIT();

	//find x using the abc-formula
	double x = (-b + sqrt(d)) / (2 * a);
	double x2 = (-b - sqrt(d)) / (2 * a);

	if (x < x2)
		t = x;
	else
		t = x2;
        
    //Compute normal
    Vector N = ((ray.O + (ray.D * t)) - p1).normalized();
    return Hit(t,N);
}
