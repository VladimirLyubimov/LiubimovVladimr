#pragma once
#include <stdio.h>
#include "structs.h"

int writePlantArray(plant* myplant, int size, FILE* fout);
int readPlant(plant* myplant, FILE* fin);