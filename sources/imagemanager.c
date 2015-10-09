#include "imagemanager.h"

int Imagemanager_DrawRect(int x, int y, int sizeX, int sizeY, Color color, Color** picture) {
    int i, j;
    for(i = 0; i < sizeX;i++) {
        for(j = 0; j < sizeY;j++){
            if(x > 0 && x < resX-1 && y > 0 && y < resY-1)
                Imagemanager_Putpixel(i,j,color,picture);
        }
    }
    return TRUE;
}

/*
Puts pixel in array. 
If succesful: return 1
If out of bounds: return 0
*/
int Imagemanager_Putpixel(int x, int y, Color color, Color** image) {
    if(x > 0 && x < resX-1 && y > 0 && y < resY-1)
        image[x][y] = color;
    else
        return FALSE;
    return TRUE;
}

int Imagemanager_FileExists(char* file) {
    return TRUE;
}

/*
Writes image to .BNM file
*/
void Imagemanager_WriteToFile(Color** image, char* fileName) {
    int i, j;
    FILE *image_file;
    image_file = fopen(fileName, "wb");

    fputs("P6\n", image_file);
    char string[20] = "ERROR";
    sprintf(string, "%d %d\n", resX, resY);
    fputs(string, image_file);
    fputs("255\n", image_file);
    for (j = 0; j < resY; j++){
        for(i = 0; i < resX; i++) {
            fputc(image[i][j].r, image_file);
            fputc(image[i][j].g, image_file);
            fputc(image[i][j].b, image_file);
        }
    }
    fclose(image_file);
}

Color** Imagemanager_AllocatePicture(int x, int y) {
    int i;
    Color** picture = malloc(x*3*sizeof(int));
    for (i = 0; i < x; ++i) {
        picture[i] = malloc(y*3*sizeof(int));
    }
    return picture;
}