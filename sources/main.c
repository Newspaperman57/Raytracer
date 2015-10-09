#include "defines.h"
#include "color.h"
#include "vector.h"
#include "ray.h"
#include "imagemanager.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    Color BACKGROUNDCOLOR;
    Color** picture = Imagemanager_AllocatePicture(resX, resY);
    
    BACKGROUNDCOLOR.r = 0;
    BACKGROUNDCOLOR.g = 0;
    BACKGROUNDCOLOR.b = 0;

    // Paint background black
    int i, j;
    for (i = 0; i < resX; ++i) {
        for (j = 0; j < resY; ++j) {
            Imagemanager_Putpixel(i, j, BACKGROUNDCOLOR, picture);
        }
    }

    Sphere s;
    int sphereCount = 2;
    Sphere spheres[sphereCount];

    s.center.x = 10;
    s.center.y = 0;
    s.center.z = 0;
    s.radius = 5;

    spheres[0] = s;
    
    s.center.x = 8;
    s.center.y = 0;
    s.center.z = 0;
    s.radius = 3;
    
    spheres[1] = s;
    
    Vector P0; // StartPoint
    P0.x = -1;
    P0.y = 0;
    P0.z = 0;

    Vector P1; // EndPoint
    P1.x = 0;

    // Calculate canvas size
    double fy = (resX > resY)? 1 : (double)resX/resY;
    double fx = (resY > resX)? 1 : (double)resY/resX;

    int x, y;
    for(x = 0; x < resX; x++) {
        for(y = 0; y < resY; y++) {
            P1.y = ((double)(x*2)/(resX-1)-1)/fx; //get relative position from -1 to 1
            P1.z = ((double)(y*2)/(resY-1)-1)/fy; //get relative position from -1 to 1
            Imagemanager_Putpixel(x, y, Ray_Cast(P0, P1, spheres, sphereCount), picture);
        }
    }

    Imagemanager_WriteToFile(picture, "output.pnm");

    for (i = 0; i < resX; ++i) {
        free(picture[i]);
    }
    free(picture);
    return 0;
}