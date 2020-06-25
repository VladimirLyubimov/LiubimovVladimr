#pragma once
#include "draw_png.h"
#include <png.h>

void DrawQueen(png* image, int x, int y, color col);
//void DrawKing(png* image, int x, int y, color col);
int PreSet(int width, int* x, int* y);//перевод координат клетки в координаты картинки