
#include "triangle.h"
#include <iostream>
#include <math.h>

#define EPSILON 0.0001

/************************** Sphere **********************************/

Hit Triangle::intersect(const Ray &ray)
{
	//GIVEN : ray.D, ray.O, normal, a,b,c
	//Using the Möller-Trumbore intersection algorithm

	Vector e1, e2, P, Q, T;
	double det, inv_det, u, v;
	double t;

	e1 = b - a;
	e2 = c - a;

	P = ray.D.cross(e2);

	det = e1.dot(P);
	if(det > -EPSILON && det < EPSILON)
		return Hit::NO_HIT();

	inv_det = 1/det;

	T = ray.O - a;

	u = T.dot(P) * inv_det;

	if (u < 0 || u > 1)
		return Hit::NO_HIT();

	Q = T.cross(e1);

	v = ray.D.dot(Q) * inv_det;

	if(v < 0 || u + v > 1)
		return Hit::NO_HIT();

	t = e2.dot(Q) * inv_det;

	if (t > EPSILON)
	{
		Vector N;
		return Hit(t,N);
	}

	return Hit::NO_HIT();

}
