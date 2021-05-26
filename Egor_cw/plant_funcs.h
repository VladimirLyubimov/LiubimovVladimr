#pragma once
#include "structs.h"
#include "stdio.h"
#include "string.h"

void initPlant(plant* myplant, const char* name, int name_len, int time, int amount, int price);

int createNewPlant(plant* myplant);