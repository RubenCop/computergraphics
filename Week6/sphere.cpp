#include "sphere.h"
#include <iostream>
#include <math.h>

#define PI 3.1415926535898
/************************** Sphere **********************************/

Hit Sphere::intersect(const Ray &ray)
{

    double a = ray.D.dot(ray.D);
    double b = (2*(ray.O - position)).dot(ray.D);
    double c = (ray.O - position).dot(ray.O - position) - r*r;

    //Calculate discriminant
    double d = b * b - 4 * a * c;

    //If discriminant is below zero: no solutions, so no intersection
    if (d < 0)
        return Hit::NO_HIT();

    //find x using the abc-formula
    double x = (-b + sqrt(d)) / (2 * a);
    double x2 = (-b - sqrt(d)) / (2 * a);

    //Determine closest intersection point
    double t = 0;
    if (x < x2)
        t = x;
    else
        t = x2;

	if (t < 0)
		return Hit::NO_HIT();

    //Normal calculation
    Vector N = ((ray.O + (ray.D * t)) - position).normalized();

    return Hit(t,N);
}

Color Sphere::getTexture(Vector N){

    Material *m = this->material;

    double c1 = this->axis.x;
    double c2 = this->axis.y;
    double c3 = this->axis.z;

    //cout << "Voor: " << rot.x << " " << rot.y << " " <<rot.z << endl;

    Vector rot = N + (r*this->axis).normalized();

    cout << "rot: " << rot << endl;
    //rot2.x = rot.x * cos(obj->angle) + (1-cos(obj->angle)) * (c1*c1*rot.x + c1*c2*rot.y + c1*c3*rot.z) + (c2*rot.z - c3*rot.y) * sin(obj->angle);
    //rot2.y = rot.y * cos(obj->angle) + (1-cos(obj->angle)) * (c2*c1*rot.x + c2*c2*rot.y + c2*c3*rot.z) + (c3*rot.x - c1*rot.z) * sin(obj->angle);
    //rot2.z = rot.z * cos(obj->angle) + (1-cos(obj->angle)) * (c3*c1*rot.x + c3*c2*rot.y + c3*c3*rot.z) + (c1*rot.y - c2*rot.x) * sin(obj->angle);

    //cout << "radius0*radius1.normal = " << (r*this->axis).normalized() << endl;

    double u = atan2(rot.y, rot.x) - (this->angle * PI / 180);
    if (u < 0)
        u += 2 * PI;
    u /= 2 * PI;

    double v = acos(rot.z) / PI;

    return m->texture->colorAt(u,v);
}
