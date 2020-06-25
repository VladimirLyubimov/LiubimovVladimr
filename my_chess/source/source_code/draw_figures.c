#include "draw_figures.h"

int PreSet(int width, int* x, int* y){
	int dd = width/8;
	*x = (*x)*dd + 1;
	*y = (*y)*dd + 1;
	return dd;
}

void DrawQueen(png* image, int xs, int ys, color col){
	int dd;
	dd = PreSet(image->width, &xs, &ys); //координаты начала верхний левый угол клетки со сдвигом на 1 по диагонали; клетки нумеруются справа налево и сверху вниз
	
	DrawLine(image, xs, ys, xs+dd/4+1, ys+dd/2+1, col);
	DrawLine(image, xs+dd/4+1, ys+dd/2+1, xs+dd/2-2, ys, col);
	DrawLine(image, xs+dd/2-1, ys, xs+3*(dd/4)-3, ys+dd/2+1, col);
	DrawLine(image, xs+3*(dd/4)-3, ys+dd/2+1, xs+dd-3, ys, col);
	DrawLine(image, xs+dd-3, ys, xs+5*(dd/6)-1, ys+dd-3, col);
	DrawLine(image, xs+5*(dd/6)-1, ys+dd-3, xs+dd/6, ys+dd-3, col);
	DrawLine(image, xs+dd/6, ys+dd-3, xs, ys, col);
	FloodFill(image, xs+dd/2, ys+2*(dd/3), col, col);
}
