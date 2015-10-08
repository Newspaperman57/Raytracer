#include <stdio.h>
#include <stdint.h>
#include <math.h>
#define resX 500
#define resY 500

/*
Following tutorial on:
    http://kylehalladay.com/blog/tutorial/math/2013/12/24/Ray-Sphere-Intersection.html
*/

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct Vector {
    double x;
    double y;
    double z;
};

struct Sphere {
    double radius;
    struct Vector center;
};

// Calculates dot product of 2 3-dimensional vectors and returns result
double Dot(double skalar, struct Vector v1) { 
    return (v1.x*skalar)+(v1.y*skalar)+(v1.z*skalar);
}

// Subtracts v2 from v1 and returns result
struct Vector Subtract(struct Vector v1, struct Vector v2) {
    v1.x -= v2.x;
    v1.y -= v2.y;
    v1.z -= v2.z;
    return v1;
}

double GetLength(struct Vector v) {
    return sqrt(pow(v.x, 2)+pow(v.y, 2)+pow(v.z, 2));
}

struct Vector Normalize(struct Vector v) {
    double length = GetLength(v);
    v.x / length;
    v.y / length;
    v.z / length;
    return v;
}

// Directly copied
double GetSphereRayIntersection(struct Sphere s, struct Vector P0, struct Vector P1) {
    //printf("\nChecking ray from %.2f x %.2f x %.2f ---> %.2f x %.2f x %.2f \nHitting sphere: %.2f x %.2f x %.2f Radius %.2f\n", P1.x, P1.y, P1.z, P0.x, P0.y, P0.z, s.center.x, s.center.y, s.center.z, s.radius);
    struct Vector d = Subtract(P1, P0); // Get the normalized vector for the ray
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

struct Color CastRay(struct Vector startPos, struct Vector endPos, struct Sphere spheres[], int sphereCount) {
    //printf("Cast ray: %.2f X %.2f X %.2F and %.2f X %.2f X %.2F\t", startPos.x, startPos.y, startPos.z, endPos.x, endPos.y, endPos.z);
    int i;
    double lowestT, hitSphere;
    lowestT = 99999999999;
    hitSphere = -1;
    double tempT;
    for (i = 0; i < sphereCount; ++i) { // Start going through all spheres to find closest hit (if any)
        //printf("\nShooting for sphere at %.2f X %.2f X %.2f R: %.2f\t", spheres[i].center.x, spheres[i].center.y, spheres[i].center.z, spheres[i].radius);
        tempT = GetSphereRayIntersection(spheres[i], startPos, endPos);
        //printf("TempT: %.2f\t", tempT);
        if ( tempT < lowestT && tempT != -1) {
            lowestT = tempT;
            hitSphere = i;
            //printf("Hit %d. sphere at %.2f X %.2f X %.2f\n", i, startPos.x+tempT*endPos.x, startPos.y+tempT*endPos.y, startPos.z+tempT*endPos.z);
        }
    }
    // Hit sphere is closest hit sphere and lowestT is where the ray hits the sphere

    struct Color color;
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

int main()
{
    struct Color BACKGROUNDCOLOR;
    struct Color picture[resX][resY];
    struct Color WHITE;

    WHITE.r = 255;
    WHITE.g = 255;
    WHITE.b = 255;

    BACKGROUNDCOLOR.r = 0;
    BACKGROUNDCOLOR.g = 0;
    BACKGROUNDCOLOR.b = 0;

    // Paint background black
    int i, j;
    for (i = 0; i < resX; ++i) {
        for (j = 0; j < resY; ++j) {
            picture[i][j] = BACKGROUNDCOLOR;
        }
    }

    struct Sphere s;
    int sphereCount = 1;
    struct Sphere spheres[sphereCount];

    s.center.x = 10;
    s.center.y = 0;
    s.center.z = 0;
    s.radius = 5;

    spheres[0] = s;
    
    s.center.x = 0;
    s.center.y = 0;
    s.center.z = 0;
    s.radius = 3;
    
    //spheres[1] = s;
    
    struct Vector P0; // StartPoint
    P0.x = -1;
    P0.y = 0;
    P0.z = 0;

    struct Vector P1; // EndPoint
    P1.x = 0;

    // Calculate canvas size
    double fy = (resX > resY)? 1 : (double)resX/resY;
    double fx = (resY > resX)? 1 : (double)resY/resX;

    int x, y;
    for(x = 0; x < resX; x++) {
        for(y = 0; y < resY; y++) {
            P1.y = ((double)(x*2)/(resX-1)-1)/fx; //get relative position from -1 to 1
            P1.z = ((double)(y*2)/(resY-1)-1)/fy; //get relative position from -1 to 1
            picture[x][y] = CastRay(P0, P1, spheres, sphereCount);
        }
    }
    
    // BNM WRITER
    FILE *image_file;

    image_file = fopen("output.pnm", "wb");

    fputs("P6\n", image_file);
    char string[20] = "ERROR";
    sprintf(string, "%d %d\n", resX, resY);
    fputs(string, image_file);
    fputs("255\n", image_file);
    for (j = 0; j < resY; j++){
        for(i = 0; i < resX; i++) {
            fputc(picture[i][j].r, image_file);
            fputc(picture[i][j].g, image_file);
            fputc(picture[i][j].b, image_file);
        }
    }

    fclose(image_file);
    
    return 0;
}