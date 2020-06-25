#pragma once

typedef struct png{
    	int width;
	int height;
	int number_of_passes;
    	png_byte color_type;
    	png_byte bit_depth;
    	png_structp png_ptr;
    	png_infop info_ptr;
    	png_bytep* row_pointers;
}png;

typedef struct RGBcolor{
	int r;
	int g;
	int b;
}color;