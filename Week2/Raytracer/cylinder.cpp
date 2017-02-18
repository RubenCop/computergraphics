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

    Triple dirVec = p2 - p1;

    Triple e = ray.D - (ray.D.dot(dirVec)/dirVec.dot(dirVec)) * dirVec;
    Triple f = (ray.O - p1) - ((ray.O - p1).dot(dirVec)/dirVec.dot(dirVec)) * dirVec;

    double a = e.dot(e);
    double b = 2 * e.dot(f);
    double c = f.dot(f) - r * r;


	double t = 0;
// 	cout << "a" << a << endl;
	//cout << b << endl;
	//cout << c << endl;

	double d = b * b - 4 * a * c;

	if (d < 0)
		return Hit::NO_HIT();

	//find x using the abc-formula
	double x = (-b + sqrt(d)) / (2 * a);
	double x2 = (-b - sqrt(d)) / (2 * a);

	//cout << x << " " << x2 << endl;

	if (x < x2)
		t = x;
	else
		t = x2;

    Point intersection = ray.O + ray.D * t;
    /*
    for (unsigned int i = 0; i < 3; i++){
        if (intersection.data[i] < p1.data[i] || intersection.data[i] > p2.data[i])
            return Hit::NO_HIT();
    }*/
    /****************************************************
    * RT1.2: NORMAL CALCULATION
    *
    * Given: t, C, r
    * Sought: N
    *
    * Insert calculation of the sphere's normal at the intersection point.
    ****************************************************/
    Vector N = ((ray.O + (ray.D * t)) - p1).normalized();

    return Hit(t,N);
}
