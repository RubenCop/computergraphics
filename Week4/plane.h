#ifndef PLANE_H
#define PLANE_H

#include "object.h"

class Plane : public Object
{
public:
    Plane(Triple normal) : normal(normal) { }

    virtual Hit intersect(const Ray &ray);

    const Triple normal;
};

#endif /* end of include guard: PLANE_H */

