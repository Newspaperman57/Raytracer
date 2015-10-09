#ifndef _IMAGEMANAGER_
#define _IMAGEMANAGER_

#include <stdio.h>
#include <stdlib.h>
#include "defines.h"
#include "color.h"

int Imagemanager_Putpixel(int, int, Color, Color**);
void Imagemanager_WriteToFile(Color**, char*);
Color** Imagemanager_AllocatePicture(int, int );

#endif