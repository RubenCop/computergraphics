#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "object.h"

class Triangle : public Object
{
public:
    Triangle(Triple a, Triple b, Triple c) : a(a), b(b), c(c) { }

    virtual Hit intersect(const Ray &ray);

    const Triple a;
    const Triple b;
    const Triple c;
};

#endif /* end of include guard: TRIANGLE_H */
