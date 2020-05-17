#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <png.h>
#include <math.h>
#include <regex.h>
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
	if (image->color_type == PNG_COLOR_TYPE_PALETTE)
	        png_set_palette_to_rgb(image->png_ptr);
    	png_read_update_info(image->png_ptr, image->info_ptr);

	if(image->bit_depth == 16)
		png_set_strip_16(image->png_ptr);
	
		
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
		printf("New size is same with old! Nothing changed (:\n");
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

void help(){
	printf("Этот мануал расскажет вам о том, как пользоваться этой программой.\nДанная прорамма работает только с png-файлами, у которых тип цвета truecolor или RGB, и имеет следующий функционал:\n 1) Для выбора изменяемого файла используйте опцию -n или --name, после которой укажите путь до изменяемого файла с расширением .png\n 2) По умолчанию изображение сохраняется в файл res.png. Для изменения файла сохранения использйте опцию -s или --save, после чего укажите путь до файла.\n 3) Рисование треугольника. Используйте опцию -t или --triangle. Аргументом этой опции является строка вида <x1,y1,x2,y2,x3,y3,red,green,blue,think,flood,red,green,blue>. Сначала идут шесть положительных чисел, меньших 10000 - коордитаны вершин, затем идёт три числа от 0 до 255 - задание цветов в RGB формате для линии, затем толщина линии, затем либо 0, либо 1, определяющая будет ли залит треугольник. Если предыдущие число - 1, то дальше идёт три числа от 0 до 255 - задание цветов в RGB формате для заливки. Числа отделяются друг от друга запятыми, пробелы отсутсвтуют.\n 4) Создание коложа из текущего изображения. Использйте опцию -c  или --collage. Дальше идут два числа, разделённых запятой: количество изображений по оси х и по оси у. Числа должны быть положительными.\n 5) Перекрашивание наибоьшего прямоугольника задного цвета. Используйте опцию -r или --repaint. Далее идёт шесть чисел от 0 до 255, разделённых запятой. Первые три числа - цвет искомого прямоугольника. Вторые - цвет для перекраски. Если прямоугольников нужного цвета нет, то изображенние не изменяется.\n 6) Опция -i  или --info показывает информацию о изображении.\n 7) Опция -h или --help показывает данный мануал.\nMade by Vladimir Lubimov, LETI, 2020\n");
}

void info(png* image, int rf){
	if(rf == 1){
		printf("Input file wasn't readed correctly!\n");
		return;
	}
	printf("Image width = %d\n", image->width);
	printf("Image height = %d\n", image->height);
	printf("Image color type = %d\n", image->color_type);
	printf("Image bit depth = %d\n", image->bit_depth);
}

int CheckArgument(const char* pattern, char* argument){
	regex_t regexp;
	regcomp(&regexp, pattern, REG_EXTENDED);
	if (regexec(&regexp, argument, 0, NULL, 0) == 0)
		return 0;
	return 1;
}

int main(int argc, char** argv){
	png image;
	//opterr = 0;

	char* opts = "n:s:c:t:r:hi";
	static struct option longopts[] = {
		{"help", no_argument, NULL, 'h'},
		{"save", required_argument, NULL, 's'},
		{"name", required_argument, NULL, 'n'},
		{"collage", required_argument, NULL, 'c'},
		{"triangle", required_argument, NULL, 't'},
		{"repaint", required_argument, NULL, 'r'},
		{"info", no_argument, NULL, 'i'},
		{NULL, 0, NULL, 0}
	};
		
	int opt;
	int inf = 0;
	int rf = 1;
	int err = 0;
	char* outfile = NULL;
	outfile = "res.png";
	char* infile = NULL;
	char* targstr = NULL;
	char* rargstr = NULL;
	char* cargstr = NULL;
	//if(argc < 2){
	//	printf("Incorrect input!\n");
	//	help();
	//	return 0;
	//}
	//printf("%d\n", argc);
	//printf("%s\n", argv[0]);
	while(opt != -1){
		//printf("%d\n", optind);
		opt = getopt_long(argc, argv, opts, longopts, &optind);
		switch(opt){
			case '?':
				printf("Wrong argument of option!\n");
				help();
				err = 1;
				break;
			case 'h':
				help();
				break;
			case 'i':
				inf = 1;	
				break;
			case 'n':
				if (CheckArgument("^.*\\w+\\.png$", optarg) || optarg == NULL){
					printf("Wrong argument of option!\n");
					help();
					err = 1;
					break;
				}
				infile = malloc(strlen(optarg) + 1);
				strcpy(infile, optarg);
				break;
			case 's':
				if (CheckArgument("^.*\\w+\\.png$", optarg) || optarg == NULL){
					printf("Wrong argument of option!\n");
					help();
					err = 1;
					break;
				}
				outfile = malloc(strlen(optarg) + 1);
				strcpy(outfile, optarg);
				break;
			case 't':
				if (CheckArgument("^[0-9]{1,4},[0-9]{1,4},[0-9]{1,4},[0-9]{1,4},[0-9]{1,4},[0-9]{1,4},[0-9]{1,3},[0-9]{1,3},[0-9]{1,3},[0-9]{1,3},[0-1](,[0-9]{1,3},[0-9]{1,3},[0-9]{1,3})?$", optarg) || optarg == NULL){
					printf("Wrong argument of option!\n");
					help();
					err = 1;
					break;
				}
				targstr = malloc(strlen(optarg) + 1);
				strcpy(targstr, optarg);
				break;
			case 'r':
				if (CheckArgument("^[0-9]{1,3},[0-9]{1,3},[0-9]{1,3},[0-9]{1,3},[0-9]{1,3},[0-9]{1,3}$", optarg) || optarg == NULL){
					printf("Wrong argument of option!\n");
					help();
					err = 1;
					break;
				}
				rargstr = malloc(strlen(optarg) + 1);
				strcpy(rargstr, optarg);
				break;
			case 'c':
				if (CheckArgument("^[0-9]{1,3},[0-9]{1,3}$", optarg) || optarg == NULL){
					printf("Wrong argument of option!\n");
					help();
					err = 1;
					break;
				}
				cargstr = malloc(strlen(optarg) + 1);
				strcpy(cargstr, optarg);
				break;
		}
	}
	rf = 1;
	if(err == 1){
		printf("Wrong options or arguments! In order to successful using please read manual higher!\n");
	}
	else{
		if (infile != NULL){
			rf = ReadFile(infile, &image);
			if (rf == 0)
				printf("Input file successfully opened!\n");
		}
		if (inf == 1){
			info(&image, rf);
		}
		if(rf != 1 && targstr != NULL){
			int x1,y1,x2,y2,x3,y3,r,g,b,th,flood;
			int fr = 0;
			int fg = 0;
			int fb = 0;
			char* pst;
			x1 = atoi(strtok(targstr,","));
			y1 = atoi(strtok(NULL,","));
			x2 = atoi(strtok(NULL,","));
			y2 = atoi(strtok(NULL,","));
			x3 = atoi(strtok(NULL,","));
			y3 = atoi(strtok(NULL,","));
			r = atoi(strtok(NULL,","));
			g = atoi(strtok(NULL,","));
			b = atoi(strtok(NULL,","));
			th = atoi(strtok(NULL,","));
			flood = atoi(strtok(NULL,","));
			pst = strtok(NULL,",");
			if(flood == 1 && pst != NULL){
				fr = atoi(pst);
				fg = atoi(strtok(NULL,","));
				fb = atoi(strtok(NULL,","));
			}
			if(x1 >= image.width || x2 >= image.width || x3 >= image.width || y1 >= image.height || y2 >= image.height || y3 >= image.height || r > 255 || g > 255 || b > 255 || fr > 255 || fg > 255 || fb > 255 || (pst == NULL && flood == 1)){
				printf("Value of argument is too big or flood fill color wasn't defined!\n");
				help();
			}
			else{
				PrintTriangle(&image,x1,y1,x2,y2,x3,y3,r,g,b,th,flood,fr,fg,fb);
				printf("Triangle successful printed!\n");
			}			
		}
		if(rargstr != NULL && rf != 1){
			int r, g, b, nr, ng, nb;
			r = atoi(strtok(rargstr,","));
			g = atoi(strtok(NULL,","));
			b = atoi(strtok(NULL,","));
			nr = atoi(strtok(NULL,","));
			ng = atoi(strtok(NULL,","));
			nb = atoi(strtok(NULL,","));
			if (r > 255 || g > 255 || b > 255 || nr > 255 || ng > 255 || nb > 255){
				printf("This color doesn't exist in RGB!\n");
				help();
			}
			else{
				Repaint(&image, r, g, b, nr, ng, nb);
				printf("The biggest rectangle of defined color repainted!\n");
			}
		}
		if(cargstr != NULL && rf != 1){
			int n,m;
			n = atoi(strtok(cargstr,","));
			m = atoi(strtok(NULL,","));
			if(n == 0 || m == 0){
				printf("Argument has value below 1! It is unacceptable!\n");
				help();
			}			
			else{
				Collage(&image, n, m);
				printf("Collage completed!\n");			
			}
		}
	}
	if(rf == 1 || err == 1){
		printf("Can't give output because of error in reading input file!\n");
		help();
	}
	else{	
		OutputImage(outfile, &image);
	}		
	return 0;
}
