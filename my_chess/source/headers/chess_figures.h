#pragma once
#include "chess_board.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Turn{
	int x;
	int y;
}turn;

typedef struct Figure{
	int x;
	int y;
	int num;
	char name;
	char color;
}figure;

figure CreateFigure(char name, int x, int y, int num, char color);
// next 3 functions returns 0 if turn possible
int LinearPattern(cboard myboard, int xs, int ys, int xf, int yf);
int DiagonalPattern(cboard myboard, int xs, int ys, int xf, int yf);
int KnightPattern(cboard myboard, int xs, int ys, int xf, int yf);
//
void MakeTurn(cboard* myboard, figure* fig, int x, int y);
int OneTurn(cboard* myboard, figure* fig, int x, int y);