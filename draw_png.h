#pragma once
#include <stdio.h>
#include <png.h>
#include <stdlib.h>
#include <math.h>
#include "struct_png.h"

void PutPixel(png_byte* ptr, color col);
void DrawLine(png* image, int x1, int y1, int x2, int y2, color col);
void DrawBoldLine(png* image, int x1, int y1, int x2, int y2, color col, int thinck);
void PictureToColor(png* image, color col);
void Square(png* image, int x1, int y1, int x2, int y2, color col);
int ColorCompare(png_byte* pixel, color col);
void FloodFill(png* image, int x, int y, color col1, color col2);//col1 color of line; col2 color of floodfill
