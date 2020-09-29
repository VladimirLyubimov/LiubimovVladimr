#pragma once
#include "MyMaze.hpp"
#include "MyPlayer.hpp"
#include <png.h>

class PNGInterface{
	private:
		int width;
		int height;
		int number_of_passes;
    	png_byte color_type;
    	png_byte bit_depth;
    	png_structp png_ptr;
    	png_infop info_ptr;
    	png_bytep* row_pointers;    	
	public:
		PNGInterface(char *filename);
		void OutputImage(char* filename);
};
