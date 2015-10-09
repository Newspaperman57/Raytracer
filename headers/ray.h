#ifndef _RAY_
#define _RAY_

#include <math.h>
#include "vector.h"
#include "sphere.h"
#include "color.h"
#include "defines.h"

double Ray_GetIntersection(Sphere, Vector, Vector);
Color Ray_Cast(Vector, Vector, Sphere*, int);
 
#endif