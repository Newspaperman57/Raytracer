#include "vector.h"

// Calculates dot product of 2 3-dimensional vectors and returns result
double Vector_Dot(double skalar, Vector v1) { 
    return (v1.x*skalar)+(v1.y*skalar)+(v1.z*skalar);
}

// Subtracts v2 from v1 and returns result
Vector Vector_Subtract(Vector v1, Vector v2) {
    v1.x -= v2.x;
    v1.y -= v2.y;
    v1.z -= v2.z;
    return v1;
}

//Calculates length of vector using pythagoras
double Vector_GetLength(Vector v) {
    return sqrt(pow(v.x, 2)+pow(v.y, 2)+pow(v.z, 2));
}

// Normalizes vector
Vector Vector_Normalize(Vector v) {
    double length = Vector_GetLength(v);
    v.x = v.x/length;
    v.y = v.y/length;
    v.z = v.z/length;
    return v;
}
