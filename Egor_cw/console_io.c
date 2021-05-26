#include "console_io.h"

void printTableLine(){
	printf("|-");
	for(int i = 0; i < 30; i++){
		printf("-");
	}
	printf("-|");
	
	printf("-");
	for(int i = 0; i < 10; i++){
		printf("-");
	}
	printf("-|");

	printf("-");
	for(int i = 0; i < 10; i++){
		printf("-");
	}
	printf("-|");

	printf("-");
	for(int i = 0; i < 10; i++){
		printf("-");
	}
	printf("-|\n");
}

void printHeader(){
	printTableLine();
	printf("|\x1b[1;32m %-30s \x1b[0m|\x1b[1;32m %-10s \x1b[0m|\x1b[1;32m %-10s \x1b[0m|\x1b[1;32m %-10s \x1b[0m|\n", "Name", "Plant time", "Amount", "Price");
	printTableLine();
}

int printPlantArray(plant* plant_arr, int size){
	if(!plant_arr){
		return 1;
	}
	
	for(int i = 0; i < size; i++){
		printf("| %-30s | %10d | %10d | %10d |\n", plant_arr[i].m_name, plant_arr[i].m_time, plant_arr[i].m_amount, plant_arr[i].m_price);
		printTableLine();
	}

	return 0;
}