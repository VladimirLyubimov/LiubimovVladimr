#include "file_io.h"

int readPlant(plant* myplant, FILE* fin){
	if(!fin){
		return 1;
	}

	fread(myplant, sizeof(plant), 1, fin);
	return 0;
}

int writePlantArray(plant* plant_arr, int arr_size, FILE* fout){
	if(!plant_arr || !fout){
		return 1;
	}

	fwrite(plant_arr, sizeof(plant), arr_size, fout);
	return 0;
}