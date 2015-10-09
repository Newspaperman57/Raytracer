#ifndef _SPHERE_
#define _SPHERE_

#include "vector.h"

typedef struct {
    double radius;
    Vector center;
} Sphere;

double Sphere_Intersect(Sphere, Vector, Vector);

#endif