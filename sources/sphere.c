#include "sphere.h"

double Sphere_Intersect(Sphere s, Vector P0, Vector P1) {
    //printf("\nChecking ray from %.2f x %.2f x %.2f ---> %.2f x %.2f x %.2f \nHitting sphere: %.2f x %.2f x %.2f Radius %.2f\n", P1.x, P1.y, P1.z, P0.x, P0.y, P0.z, s.center.x, s.center.y, s.center.z, s.radius);
    Vector d = Vector_Subtract(P1, P0); // Get the normalized vector for the ray
    double a = d.x*d.x + d.y*d.y + d.z*d.z;
    double b = 2*d.x*(P0.x-s.center.x) + 2*d.y*(P0.y-s.center.y) + 2*d.z*(P0.z-s.center.z);
    double c = s.center.x*s.center.x + s.center.y*s.center.y + s.center.z*s.center.z +
                P0.x*P0.x + P0.y*P0.y + P0.z*P0.z + 
                -2*(s.center.x*P0.x + s.center.y*P0.y + s.center.z*P0.z) - 
                s.radius*s.radius;
    double disabc = b*b-4*a*c;
    if(disabc < 0){
        //printf("Disabs is below 0: %f\n", disabc);
        return -1;
    }
    double t = (-b-sqrt(b*b-4*a*c))/(2*a);
    if(t > 0)
        return t;
    return -1;
}