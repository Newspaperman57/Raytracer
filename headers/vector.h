#ifndef _VECTOR_
#define _VECTOR_


#include <math.h>

typedef struct { 
    double x;
    double y;
    double z;
} Vector;

double Vector_Dot(double, Vector);
Vector Vector_Subtract(Vector, Vector);
double Vector_GetLength(Vector);
Vector Vector_Normalize(Vector);
 
#endif