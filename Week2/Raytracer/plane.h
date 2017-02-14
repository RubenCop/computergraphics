#ifndef PLANE_H
#define PLANE_H

#include "object.h"

class Plane : public Object
{
public:
    Plane(Triple normal,double d) : normal(normal), d(d) { }

    virtual Hit intersect(const Ray &ray);

    const Triple normal;
    const double d;
};

#endif /* end of include guard: PLANE_H */

