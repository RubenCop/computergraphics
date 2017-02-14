
#include "triangle.h"
#include <iostream>
#include <math.h>

/************************** Sphere **********************************/

Hit Triangle::intersect(const Ray &ray)
{
	//GIVEN : ray.D, ray.O, normal, d, a,b,c
	Triple U = b - a;
	Triple V = c - a;
	
	double x = U.data[1]*V.data[2] - U.data[2] * V.data[1];
	double y = U.data[2]*V.data[0] - U.data[0] * V.data[2];
	double z = U.data[0]*V.data[1] - U.data[1] * V.data[0];
	Triple normal(x,y,z);
	
	double t = (-((ray.O).dot(normal) + d)) / (ray.D.dot(normal));
	
	Triple intersect = ray.O + (ray.D * t);
	
	for (unsigned int i = 0; i < 3; i++) // loop through x y z coordinates
	{
		double minimum = 99999999;
		double maximum = -99999999;
		/*cout << "z coordinate a: " << a.data[i] << endl;
		cout << "z coordinate b: " << b.data[i] << endl;
		cout << "z coordinate c: " << c.data[i] << endl;
		cout << "intersect z: " << intersect.data[i] << endl;*/
		if (a.data[i] < minimum)
			minimum = a.data[i];
		if (b.data[i] < minimum)
			minimum = b.data[i];
		if (c.data[i] < minimum)
			minimum = c.data[i];
		if (a.data[i] > maximum)
			maximum = a.data[i];
		if (b.data[i] > maximum)
			maximum = b.data[i];
		if (c.data[i] > maximum)
			maximum = c.data[i];
		
		if (!(intersect.data[i] >= minimum && intersect.data[i] <= maximum))
		{
			//cout << "intersect" << intersect.data[i] << endl;
			//cout << "maximum" << maximum << endl;
			//cout << "minimum" << minimum << endl;
			return Hit::NO_HIT();
		}
			
	}
	cout << "hit" << endl;
    return Hit(t,normal);
}


