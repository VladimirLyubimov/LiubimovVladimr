#pragma once
#include <stdlib.h>

typedef struct cell{
	char color;
	int isEmpty;
	int fig_num;
}cell;

typedef struct ChessBoard{
	cell** board;
}cboard;

int isCellEmpty(cell mycell);//1 если клетка свободна
void init(cboard* myboard);
void myFree(cboard* myboard);