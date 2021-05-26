#include "plant_funcs.h"

void initPlant(plant* myplant, const char* name, int name_len, int time, int amount, int price){
	int i = 0;
	for(i = 0; i < name_len; i++){
		myplant->m_name[i] = name[i];
	}
	myplant->m_name[i] = '\0';

	myplant->m_time = time;
	myplant->m_amount = amount;
	myplant->m_price = price;
}

int createNewPlant(plant* myplant){
	char name[31];
	int time, amount, price;

	printf("Input plant name:\n");
	scanf("%s", name);
	printf("Input planting time, amount of seeds and price divided by space:\n");
	scanf("%d %d %d", &time, &amount, &price);

	if(time < 1 || time > 12 || amount < 0 || price < 0){
		return 1;
	}

	initPlant(myplant, name, strlen(name), time, amount,price);

	return 0;
}