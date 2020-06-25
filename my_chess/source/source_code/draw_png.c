#include "draw_png.h"

void PutPixel(png_byte* ptr, color col){
	ptr[0] = col.r;
	ptr[1] = col.g;
	ptr[2] = col.b;
}

void DrawLine(png* image, int x1, int y1, int x2, int y2, color col){
	int deltax = abs(x2 - x1);
    	int deltay = abs(y2 - y1);
    	int dX = x1 < x2 ? 1 : -1;
    	int dY = y1 < y2 ? 1 : -1;
    	int error = deltax - deltay;

	png_byte* row = image->row_pointers[y2];
	png_byte* ptr = &(row[x2*3]);
	PutPixel(ptr, col);    	

	while(x1 != x2 || y1 != y2) {
		png_byte* row = image->row_pointers[y1];
		png_byte* ptr = &(row[x1*3]);
		PutPixel(ptr, col);
        	int error2 = error * 2;
        	
	        if(error2 > -deltay){
            		error -= deltay;
            		x1 += dX;
        	}
	
        	if(error2 < deltax){
            		error += deltax;
            		y1 += dY;
        	}
    	} 
}

void DrawBoldLine(png* image, int x1, int y1, int x2, int y2, color col, int thinck){
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int dd = dx - dy;
	int i = -thinck/2;
	if(thinck == 1){
		DrawLine(image, x1, y1, x2, y2, col);	
	}

	if (dd > 0){
		for(i; i < thinck/2; i++){
			DrawLine(image, x1, y1+i, x2, y2+i, col);
		}
	}
	else{
		for(i; i < thinck/2; i++){
			DrawLine(image, x1+i, y1, x2+i, y2, col);
		}
	}
}

void PictureToColor(png* image, color col){
	int j = 0;
	int i = 0;
	for (i; i < image->height; i++){
		j = 0;
		for (j; j < image->width; j++){
			PutPixel(&image->row_pointers[i][j*3], col);
		}
	}
}

void Square(png* image, int x1, int y1, int x2, int y2, color col){
	int i = x1;
	for(i; i <=x2; i++){
		DrawLine(image, i, y1, i, y2, col);
	}
}

int ColorCompare(png_byte* pixel, color col){
	if(pixel[0] == col.r && pixel[1] == col.g && pixel[2] == col.b)
		return 1;
	return 0; 
}


void FloodFill(png* image, int x, int y, color col1, color col2){
	if(ColorCompare(&(image->row_pointers[y][x*3]), col1) || ColorCompare(&(image->row_pointers[y][x*3]), col2)){		
		return;
	}
	PutPixel(&image->row_pointers[y][x*3], col2);
	FloodFill(image, x-1, y, col1, col2);
	FloodFill(image, x+1, y, col1, col2);
	FloodFill(image, x, y-1, col1, col2);
	FloodFill(image, x, y+1, col1, col2);
	return;
}