#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <png.h>
#include <math.h>
#define PNG_DEBUG 3

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

int ReadFile(char *filename, png* image) {
    	int x,y;
	x = 0;
	y = 0;
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
	image->bit_depth = png_get_bit_depth(image->png_ptr, image->info_ptr);
	image->color_type = png_get_color_type(image->png_ptr, image->info_ptr);
	image->number_of_passes = png_set_interlace_handling(image->png_ptr);
    	png_read_update_info(image->png_ptr, image->info_ptr);

	//if(image->bit_depth == 16)
		//png_set_strip_16(image->png_ptr);
		
	if (setjmp(png_jmpbuf(image->png_ptr))){
		fprintf(stderr, "Error during reading image!\n");
		return 1;
	}

	image->row_pointers = (png_bytep*)malloc(image->height * sizeof(png_bytep));
	for(y = 0; y < image->height; y++){
		image->row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(image->png_ptr, image->info_ptr));
	}
	png_read_image(image->png_ptr, image->row_pointers);
    	fclose(fl);
	
	return 0;
}

int OutputImage(char* filename, png* image){
	FILE* fl = fopen(filename, "wb");
	if(!fl){
		fprintf(stderr, "File could not be opened!\n");
		return 1;
	}

	image->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if(!image->png_ptr){
		fprintf(stderr, "png_create_write_struct failed!\n");
		return 1;
	}

	image->info_ptr = png_create_info_struct(image->png_ptr);
	if(!image->png_ptr){
		fprintf(stderr, "png_create_info_struct failed!\n");
		return 1;
	}

	if (setjmp(png_jmpbuf(image->png_ptr))){
	        printf("Error during init_io!\n");
		return 1;
    	}

	png_init_io(image->png_ptr, fl);

	if (setjmp(png_jmpbuf(image->png_ptr))){
	        printf("Error during writing header!\n");
		return 1;
    	}

	png_set_IHDR(image->png_ptr, image->info_ptr, image->width, image->height, image->bit_depth, image->color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);	
	
	png_write_info(image->png_ptr, image->info_ptr);
	
	if (setjmp(png_jmpbuf(image->png_ptr))){
	        printf("Error during writing image!\n");
		return 1;
    	}

	png_write_image(image->png_ptr, image->row_pointers);

	if (setjmp(png_jmpbuf(image->png_ptr))){
	        printf("Error during the end of writing!\n");
		return 1;
    	}

	png_write_end(image->png_ptr, NULL);

	fclose(fl);

	return 0;
}

void PutPixel(int r, int b, int g, png_byte* ptr){
	ptr[0] = r;
	ptr[1] = b;
	ptr[2] = g;
}

void swap(int* a, int* b){
	int c = *a;
	*a = *b;
	*b = c;
}

void DrawLine(png* image, int x1, int y1, int x2, int y2){//алгоритм Брезенхэма
	int deltaX = abs(x2 - x1);
    	int deltaY = abs(y2 - y1);
    	int signX = x1 < x2 ? 1 : -1;
    	int signY = y1 < y2 ? 1 : -1;
    //
    int error = deltaX - deltaY;
    //
    //setPixel(x2, y2);
    while(x1 != x2 || y1 != y2) 
   {
        printf("x = %d y = %d\n", x1, y1);
		png_byte* row = image->row_pointers[y1];
		png_byte* ptr = &(row[x1*3]);
		PutPixel(0, 0, 0, ptr);
        int error2 = error * 2;
        //
        if(error2 > -deltaY) 
        {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX) 
        {
            error += deltaX;
            y1 += signY;
        }
    }
 
}


int main(int argc, char** argv){
	png image;
	//image = (png*)malloc(1*sizeof(png));
	ReadFile(argv[1], &image);
	printf("%d %d\n", image.width, image.height);
	DrawLine(&image, 100, 10, 500, 100);
	OutputImage(argv[2], &image);		
	return 0;
}
