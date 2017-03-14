//
//  Framework for a raytracer
//  File: sphere.h
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

#ifndef TORUS_H
#define TORUS_H

#include "object.h"

class Torus : public Object
{
public:
    Torus(Point position,double r1, double r2) : position(position), r1(r1), r2(r2) { }

    virtual Hit intersect(const Ray &ray);

    const Point position;
    const double r1;
    const double r2;
};

#endif /* end of include guard: SPHERE_H_115209AE */
