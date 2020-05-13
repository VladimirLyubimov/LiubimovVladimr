#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <png.h>

typedef struct png{
    	int width;
	int height;
	int number_of_passes;
    	png_byte color_type;
    	png_byte bit_depth;
    	png_structp png_ptr;
    	png_infop info_ptr;
    	png_bytep *row_pointers;
}png;

int ReadFile(char *filename, png* image) {
    	int x,y;
    	char header[8];
    	FILE *fl = fopen(filename, "rb");
    	if (!fl){
		fprintf(stderr, "File could not be opened!\n");
		return 1;    	
	}
    	
	fread(header, 1, 8, fl);
    	if (png_sig_cmp(header, 0, 8)){
		fprintf(stderr, "File is not png-type file!\n");
		return 1;
    	}

    	image->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    	if (!image->png_ptr){
		fprintf(stderr, "png_create_read_struct failed!\n");
		return 1;
    	}
    	image->info_ptr = png_create_info_struct(image->png_ptr);
    	if (!image->info_ptr){
		fprintf(stderr, "png_create_info_struct failed!\n");
		return 1;
    	}

	if (setjmp(png_jmpbuf(image->png_ptr))){
		fprintf(stderr, "Error during init_io!\n");
		fclose(fl);
		return 1;
	}
	
	png_init_io(image->png_ptr, fl);
	png_set_sig_bytes(image->png_ptr, 8);

	png_read_info(image->png_ptr, image->info_ptr);

	image->width = png_get_image_width(image->png_ptr, image->info_ptr);
	image->height = png_get_image_height(image->png_ptr, image->info_ptr);
}


int main(int argc, char** argv){
	png* image;
	image = malloc(1*sizeof(png));
	ReadFile(argv[1], image);		
	return 0;
}
