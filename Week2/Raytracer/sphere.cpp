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

#include "sphere.h"
#include <iostream>
#include <math.h>

/************************** Sphere **********************************/

Hit Sphere::intersect(const Ray &ray)
{
    /****************************************************
    * RT1.1: INTERSECTION CALCULATION
    *
    * Given: ray, position, r
    * Sought: intersects? if true: *t
    * 
    * Insert calculation of ray/sphere intersection here. 
    *
    * You have the sphere's center (C) and radius (r) as well as
    * the ray's origin (ray.O) and direction (ray.D).
    *
    * If the ray does not intersect the sphere, return false.
    * Otherwise, return true and place the distance of the
    * intersection point from the ray origin in *t (see example).
    ****************************************************/

    // place holder for actual intersection calculation

	double a = ray.D.dot(ray.D);
	double b = (2*(ray.O - position)).dot(ray.D);
	double c = (ray.O - position).dot(ray.O - position) - r*r;
	
	double t = 0;
// 	cout << "a" << a << endl;
	//cout << b << endl;
	//cout << c << endl;
	
	double d = sqrt(b * b - 4 * a * c);
	
	if (d < 0)
		return Hit::NO_HIT();
	
	//find x using the abc-formula
	double x = (-b + d) / (2 * a); 
	double x2 = (-b - d) / (2 * a); 
	
	//cout << x << " " << x2 << endl;
	
	if (x < x2)
		t = x;
	else 
		t = x2;
    /****************************************************
    * RT1.2: NORMAL CALCULATION
    *
    * Given: t, C, r
    * Sought: N
    * 
    * Insert calculation of the sphere's normal at the intersection point.
    ****************************************************/
    Vector N /* = ... */;

    return Hit(t,N);
}
