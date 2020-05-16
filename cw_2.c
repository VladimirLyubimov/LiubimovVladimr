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

void PrintLine(png* image, int x1, int y1, int x2, int y2, int r, int g, int b){//алгоритм Брезенхэма
	int deltax = abs(x2 - x1);
    	int deltay = abs(y2 - y1);
    	int dX = x1 < x2 ? 1 : -1;
    	int dY = y1 < y2 ? 1 : -1;
    	int error = deltax - deltay;

	//int arr[deltax];

	png_byte* row = image->row_pointers[y2];
	png_byte* ptr = &(row[x2*3]);
	PutPixel(r, g, b, ptr);    	

	while(x1 != x2 || y1 != y2) {
        	//printf("x = %d y = %d\n", x1, y1);
		png_byte* row = image->row_pointers[y1];
		png_byte* ptr = &(row[x1*3]);
		PutPixel(r, g, b, ptr);
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

void PrintLineWithGivenThickness(png* image, int x1, int y1, int x2, int y2, int r, int g, int b, int th){
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int dd = dx - dy;
	int i = -th/2;
	if(th == 1){
		PrintLine(image, x1, y1, x2, y2, r, g, b);	
	}

	if (dd > 0){
		for(i; i < th/2; i++){
			if(y1 + i < 0){
				if (x1 - i <= image->width-1){	
					PrintLine(image, x1-i, y1, x2, y2+i, r, g, b);
					continue;
				}
				else{
					PrintLine(image, x1+i, y1, x2, y2+i, r, g, b);
					continue;				
				}
			}
			if(y2 + i > image->height-1){
				if (x2 - i >= 0){	
					PrintLine(image, x1, y1+i, x2-i, y2, r, g, b);
					continue;
				}
				else{
					PrintLine(image, x1, y1+i, x2+i, y2, r, g, b);
					continue;
				}	
			}

			if(y2 + i < 0){
				if (x2 - i <= image->width-1){	
					PrintLine(image, x1, y1+i, x2-i, y2, r, g, b);
					continue;
				}
				else{
					PrintLine(image, x1, y1+i, x2+i, y2, r, g, b);
					continue;				
				}
			}
			if(y1 + i > image->height-1){
				if (x1 - i >= 0){	
					PrintLine(image, x1-i, y1, x2, y2+i, r, g, b);
					continue;
				}
				else{
					PrintLine(image, x1+i, y1, x2, y2+i, r, g, b);
					continue;
				}	
			}
			PrintLine(image, x1, y1+i, x2, y2+i, r, g, b);
		}
	}
	else{
		for(i; i < th/2; i++){
			if(x1 + i < 0){
				if (y1 - i <= image->height-1){	
					PrintLine(image, x1, y1-i, x2+i, y2, r, g, b);
					continue;
				}
				else{
					PrintLine(image, x1, y1+i, x2+i, y2, r, g, b);
					continue;				
				}
			}
			if(x2 + i > image->width-1){
				if (y2 - i >= 0){	
					PrintLine(image, x1+i, y1, x2, y2-i, r, g, b);
					continue;
				}
				else{
					PrintLine(image, x1+i, y1, x2, y2+i, r, g, b);
					continue;
				}	
			}

			if(x2 + i < 0){
				if (y2 - i <= image->height-1){	
					PrintLine(image, x1+i, y1, x2, y2-i, r, g, b);
					continue;
				}
				else{
					PrintLine(image, x1+i, y1, x2, y2+i, r, g, b);
					continue;				
				}
			}
			if(x1 + i > image->width-1){
				if (y1 - i >= 0){	
					PrintLine(image, x1, y1-i, x2+i, y2, r, g, b);
					continue;
				}
				else{
					PrintLine(image, x1, y1+i, x2+i, y2, r, g, b);
					continue;
				}	
			}
			PrintLine(image, x1+i, y1, x2+i, y2, r, g, b);
		}
	}	
}

int ColorCompare(png_byte* pixel, int r, int g, int b){
	if(pixel[0] == r && pixel[1] == g && pixel[2] == b)
		return 1;
	return 0; 
}

void FloodFill(png* image, int xs, int ys, int r, int g, int b, int ir, int ig, int ib){//рекурсивный алгоритм заливки
	//printf("%d %d\n", xs, ys);
	if(ColorCompare(&(image->row_pointers[ys][xs*3]), r, g, b) || ColorCompare(&(image->row_pointers[ys][xs*3]), ir, ig, ib)){
		//printf("%d %d\n", xs, ys);		
		return;
	}
	image->row_pointers[ys][xs*3] = ir;
	image->row_pointers[ys][xs*3+1] = ig;
	image->row_pointers[ys][xs*3+2] = ib;
	FloodFill(image, xs-1, ys, r, g, b, ir, ig, ib);
	FloodFill(image, xs+1, ys, r, g, b, ir, ig, ib);
	FloodFill(image, xs, ys-1, r, g, b, ir, ig, ib);
	FloodFill(image, xs, ys+1, r, g, b, ir, ig, ib);
	return;	
}

void PrintTriangle(png* image, int x1, int y1, int x2, int y2, int x3, int y3, int r, int g, int b, int th, int flood_fill, int ir, int ig, int ib){
	PrintLineWithGivenThickness(image, x1, y1, x2, y2, r, g, b, th);
	PrintLineWithGivenThickness(image, x1, y1, x3, y3, r, g, b, th);
	PrintLineWithGivenThickness(image, x2, y2, x3, y3, r, g, b, th);
	if (flood_fill == 1){
		FloodFill(image, (x1+x2+x3)/3, (y1+y2+y3)/3, r, g, b, ir, ig, ib);
		//float dy =
	}
	//PrintLineWithGivenThickness(image, x1, y1, x1+th/2, y1+th/2, r, g, b, th);
}

void YCollage(png* image, int m){
	image->row_pointers = (png_bytep*)realloc(image->row_pointers, m*image->height*sizeof(png_bytep));
	int i = image->height;	
	for(i; i < image->height*m; i++){
		image->row_pointers[i] = image->row_pointers[i-image->height];
	}
	image->height *= m;
	
}

void XCollage(png* image, int n){
	int i = 0;
	png_bytep* row_pointers2;
	row_pointers2 = (png_bytep*)calloc(sizeof(png_bytep), image->height);	
	for(i; i < image->height; i++){
		row_pointers2[i] = (png_byte*)calloc(sizeof(png_byte), n*image->width*3);
	}

	int k = 0;
	int j = image->width;
	png_byte* ptr;
	png_byte* row;
	for(k; k < n; k++){
	i  = 0;	
	for(i; i < image->height; i++){
		row = image->row_pointers[i];
		j = 0;
		for(j; j < image->width; j++){
			ptr = &(row[j*3]);

			row_pointers2[i][(j+image->width*k)*3] = ptr[0];
			row_pointers2[i][(j+image->width*k)*3+1] = ptr[1];
			row_pointers2[i][(j+image->width*k)*3+2] = ptr[2];
		}
	}
	}
	image->width *= n;
	image->row_pointers = row_pointers2;	
}

void Collage(png* image, int n, int m){
	if(n == 1 && m == 1){
		printf("New size is same with old!\n");
		return;
	}
	XCollage(image, n);
	YCollage(image, m);	
}

typedef struct RecTangle{
	int xl;
	int yl;
	int xr;
	int yr;
	int sq;
}rec;

rec FindRectangle(png* image, int xs, int ys, int r, int g, int b){
	int xtl = xs;
	int ytl = ys;
	rec outrec;
	while(ColorCompare(&(image->row_pointers[ys][xs*3]), r, g, b) && xs < image->width)
		xs += 1;
	int xtr = xs-1;
	int mr = 0;
	int mg = 0;
	int mb = 0;
	if(mr == r && mg == g && mb == b)
		mr = 255;
	if(xtr<xtl){
		PrintLine(image, xtl, ytl, xtl, ys, mr, mg, mb);
		outrec.xl = xtl;
		outrec.yl = ytl;
		outrec.xr = xtl;
		outrec.yr = ys;
		outrec.sq = 0;
		return outrec;
	}
	PrintLine(image, xtl, ys, xtr, ys, mr, mg, mb);
	ys += 1;
	while(ys < image->height-1 && ColorCompare(&(image->row_pointers[ys][xtl*3]), r, g, b) && xtr == xs-1){
		xtr = xs-1;		
		xs = xtl;
		while(ColorCompare(&(image->row_pointers[ys][xs*3]), r, g, b) && xs < image->width)
			xs += 1;
		PrintLine(image, xtl, ys, xs-1, ys, mr, mg, mb);
		ys += 1;
	}
	outrec.xl = xtl;
	outrec.yl = ytl;
	outrec.xr = xtr;
	outrec.yr = ys;
	outrec.sq = (xtr - xtl)*((ys) - ytl);
	return outrec;
}

int cmp(const void* el1, const void* el2){
	rec e1 = *(rec*)el1;
	rec e2 = *(rec*)el2;
	if(e1.sq > e2.sq)
		return 1;
	if(e1.sq == e2.sq)
		return 0;
	if(e1.sq < e2.sq)
		return -1;

}

rec GetAllRecs(png* image, int r, int g, int b){
	rec* reclist = (rec*)calloc(1,sizeof(rec));
	rec outrec;
	int i = 0;
	int j;
	int k = 0;
	for(i; i < image->height; i++){
		j = 0;
		for (j; j < image->width; j++){
			reclist[k] = FindRectangle(image, j, i, r, g, b);
			k += 1;
			reclist = (rec*)realloc(reclist, sizeof(rec)*(k+1));
		}
	}
	qsort(reclist, k, sizeof(rec), cmp);
	outrec = reclist[k-1];
	return outrec; 
}

void Repaint(png* image, int r, int g, int b, int nr, int ng, int nb){
	int i = 0;
	png_bytep* row_pointers2;
	row_pointers2 = (png_bytep*)calloc(sizeof(png_bytep), image->height);	
	for(i; i < image->height; i++){
		row_pointers2[i] = (png_byte*)calloc(sizeof(png_byte), image->width*3);
	}
	i  = 0;
	png_byte* ptr;
	png_byte* row;
	int j;	
	for(i; i < image->height; i++){
		row = image->row_pointers[i];
		j = 0;
		for(j; j < image->width; j++){
			ptr = &(row[j*3]);

			row_pointers2[i][j*3] = ptr[0];
			row_pointers2[i][j*3+1] = ptr[1];
			row_pointers2[i][j*3+2] = ptr[2];
		}
	}
	
	rec myrec = GetAllRecs(image, r, g, b);
	image->row_pointers = row_pointers2;
	i = myrec.xl;
	for (i; i <= myrec.xr; i++){
		PrintLine(image, i, myrec.yl, i, myrec.yr, nr, ng, nb);
	}
}

int main(int argc, char** argv){
	png image;
	ReadFile(argv[1], &image);
	printf("%d %d\n", image.width, image.height);
	//PrintTriangle(&image, 0, 0, 0, 150, 300, 150, 255, 255, 0, 2, 1, 100, 0, 0);
	PrintLineWithGivenThickness(&image, 0, 10, 300, 10, 0, 100, 0, 20);
	PrintLineWithGivenThickness(&image, 0, 100, 200, 100, 0, 100, 0, 20);
	//GetAllRecs(&image, 0, 100, 0);
	Repaint(&image, 0, 100, 0, 255, 0, 0);
	//Collage(&image, 1, 1);
	//PrintLineWithGivenThickness(&image, 0, 0, 200, 200,  0, 0, 255, 30);
	//image.row_pointers = ChangeSize(&image, 150, 100);
	//image.width = 150;
	//image.height = 100;
	//PrintLineWithGivenThickness(&image, 0, 0, 100, 50,  0, 0, 255, 30);
	printf("%d %d\n", image.width, image.height);
	OutputImage(argv[2], &image);		
	return 0;
}
