#ifndef SPHERE_H_115209AE
#define SPHERE_H_115209AE

#include "object.h"

class Sphere : public Object
{
public:
    Sphere(Point position,double r) : position(position), r(r) { }

    virtual Hit intersect(const Ray &ray);
	
    const Point position;
    const double r;
};

#endif /* end of include guard: SPHERE_H_115209AE */
