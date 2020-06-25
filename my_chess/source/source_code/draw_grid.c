#include "draw_grid.h"

void DrawTwoColorSquareGrid(png* image, color col1, color col2,int square_amount){
	PictureToColor(image, col1);
	
	if (image->height >= image->width)
		image->height = image->width;
	else
		image->width = image->height;

	int size = image->width/square_amount;

	int i = 0;
	int j = 0;
	for(j; j < square_amount; j++){
		for(i; i < square_amount; i++){
			if((i%2 == 0 && j%2 == 0) || (i%2 == 1 && j%2 == 1)){
				Square(image, (i+1)*size, size*j, (i+2)*size-1, (j+1)*size-1, col2);
			}
			else{
				Square(image, i*size, size*j, (i+1)*size-1, (j+1)*size-1, col2);

			}
		}
		i = 0;
	}
}