
#include "triangle.h"
#include <iostream>
#include <math.h>
#define EPSILON 0.00001

/************************** Sphere **********************************/

Hit Triangle::intersect(const Ray &ray)
{
	//Ray-triangle intersection using the Möller-Trumbore intersection algorithm:
	//https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm

	//cout << "ik ben een driehoek" << endl;

	//GIVEN : ray.D, ray.O, normal, d, a,b,c
	Vector e1, e2, P, Q, T;
	double det, inv_det, u, v;
	double t;

	//Vectors for the edges
	e1 = b - a;
	e2 = c - a;

	//Calculate determinant
	P = ray.D.cross(e2);
	det = e1.dot(P);

	//If det = 0, no solutions so no hit
	if(det > -EPSILON && det < EPSILON)
		return Hit::NO_HIT();

	//Test if intersection is within bounds of the triangle
	inv_det = 1/det;
	T = ray.O - a;
	u = T.dot(P) * inv_det;
	if (u < 0 || u > 1)
		return Hit::NO_HIT();

	//Test if intersection is within bounds of the triangle
	Q = T.cross(e1);
	v = ray.D.dot(Q) * inv_det;
	if(v < 0 || u + v > 1)
		return Hit::NO_HIT();

	//Calulate distance
	t = e2.dot(Q) * inv_det;

	//In case of a hit, calculate normal and return distance + normal
	if (t > EPSILON)
	{
		Vector N;
		Triple A, B;
		A = b-a;
		B = c-a;
		N = A.cross(B);
		if (N.dot(ray.D)>0)
		{
			N = N * -1;
		}
		cout << "auw" << endl;
		return Hit(t,N.normalized());
	}

	return Hit::NO_HIT();

}
