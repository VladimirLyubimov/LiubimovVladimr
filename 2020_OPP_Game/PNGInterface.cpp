#include "PNGInterface.hpp"

PNGInterface::PNGInterface(char *filename){
	int x,y;
	x = 0;
	y = 0;
    char header[8];
    
    FILE *fl = fopen(filename, "rb");    	
	fread(header, 1, 8, fl);
    
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    info_ptr = png_create_info_struct(png_ptr);
   	png_init_io(png_ptr, fl);
	png_set_sig_bytes(png_ptr, 8);
	png_read_info(png_ptr, info_ptr);
	width = png_get_image_width(png_ptr, info_ptr);
	height = png_get_image_height(png_ptr, info_ptr);
	bit_depth = png_get_bit_depth(png_ptr, info_ptr);
	color_type = png_get_color_type(png_ptr, info_ptr);
	number_of_passes = png_set_interlace_handling(png_ptr);
    png_read_update_info(png_ptr, info_ptr);

	row_pointers = (png_bytep*)malloc(height * sizeof(png_bytep));
	for(y = 0; y < height; y++){
		row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png_ptr, info_ptr));
	}
	png_read_image(png_ptr, row_pointers);
    fclose(fl);
}

void PNGInterface::OutputImage(char* filename){
	FILE* fl = fopen(filename, "wb");
		
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	info_ptr = png_create_info_struct(png_ptr);
	png_init_io(png_ptr, fl);

	png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);	
	
	png_write_info(png_ptr, info_ptr);
	
	png_write_image(png_ptr, row_pointers);
	png_write_end(png_ptr, NULL);

	fclose(fl);
}
