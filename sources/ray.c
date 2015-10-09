#include "ray.h"

// Directly copied
double Ray_GetIntersection(Sphere s, Vector P0, Vector P1) {
    return Sphere_Intersect(s, P0, P1);
}

Color Ray_Cast(Vector startPos, Vector endPos, Sphere spheres[], int sphereCount) {
    //printf("Cast ray: %.2f X %.2f X %.2F and %.2f X %.2f X %.2F\t", startPos.x, startPos.y, startPos.z, endPos.x, endPos.y, endPos.z);
    int i;
    double lowestT, hitSphere;
    lowestT = 99999999999;
    hitSphere = -1;
    double tempT;
    for (i = 0; i < sphereCount; ++i) { // Start going through all spheres to find closest hit (if any)
        //printf("\nShooting for sphere at %.2f X %.2f X %.2f R: %.2f\t", spheres[i].center.x, spheres[i].center.y, spheres[i].center.z, spheres[i].radius);
        tempT = Ray_GetIntersection(spheres[i], startPos, endPos);
        //printf("TempT: %.2f\t", tempT);
        if ( tempT < lowestT && tempT != -1) {
            lowestT = tempT;
            hitSphere = i;
            //printf("Hit %d. sphere at %.2f X %.2f X %.2f\n", i, startPos.x+tempT*endPos.x, startPos.y+tempT*endPos.y, startPos.z+tempT*endPos.z);
        }
    }
    // Hit sphere is closest hit sphere and lowestT is where the ray hits the sphere

    Color color;
    // Temp solution to colors to different circles 
    if(hitSphere == 0) {
        color.r = 255;
        color.g =   0;
        color.b =   0;
        //printf("Hit 1!");
    } else if(hitSphere == 1) {
        color.r =   0;
        color.g = 255;
        color.b =   0;
        //printf("Hit 2!");
    } else {
        color.r =   0;
        color.g =   0;
        color.b =   0;
    }
    //printf("\n");
    return color;
}