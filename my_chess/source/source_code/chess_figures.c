#include "chess_figures.h"

figure CreateFigure(char name, int x, int y, int num, char color){
	figure fig = {x, y, num, name, color};
	return fig;
}

int LinearPattern(cboard myboard, int xs, int ys, int xf, int yf){
	int dx = xs - xf;
	int dy = ys - yf;
	int ddx = 0;
	int ddy = 0;
	
	if(dx == dy){
		//fprintf(stderr, "Wrong input data!\n");
		return 1;
	}

	if(dx == 0)
		ddy = dy < 0 ? 1: -1;
	if(dy == 0)
		ddx = dx < 0 ? 1: -1;

	while(xs != xf && yf != ys){
		ys += ddy;
		xs += ddx;
		if(!isCellEmpty(myboard.board[ys][xs]))
			return 1;
	}
	return 0;
}

int DiagonalPattern(cboard myboard, int xs, int ys, int xf, int yf){
	int dx = xs - xf;
	int dy = ys - yf;
	
	if(abs(dx) != abs(dy)){
		//fprintf(stderr, "Wrong input data!\n");
		return 1;
	}
	
	int ddy = dy < 0 ? 1: -1;
	int ddx = dx < 0 ? 1: -1;

	while(xs != xf && yf != ys){
		ys += ddy;
		xs += ddx;
		if (!isCellEmpty(myboard.board[ys][xs]))
			return 1;
	}
	return 0;
}

int KnightPattern(cboard myboard, int xs, int ys, int xf, int yf){
	int dx = abs(xs - xf);
	int dy = abs(ys - yf);
	if((dx+1)*(dx+1) + (dy+1)*(dy+1) == 13){
		if(isCellEmpty(myboard.board[yf][xf])){
			return 0;
	}	
	}
	fprintf(stderr, "Wrong input data!\n");
	return 1;
}

void MakeTurn(cboard* myboard, figure* fig, int x, int y){
	myboard->board[fig->y][fig->x].isEmpty = 1;
	myboard->board[fig->y][fig->x].fig_num = -1;
	fig->x = x;
	fig->y = y;
	myboard->board[y][x].isEmpty = 0;
	myboard->board[y][x].fig_num = fig->num;
}

int OneTurn(cboard* myboard, figure* fig, int x, int y){
	if(x > 7 || x < 0 || y > 7 || y < 0){
		fprintf(stderr, "Invalid coordinates!\n");
		return 1;
	}

	switch(fig->name){
		case 'k': //король
			if(LinearPattern(*myboard, fig->x, fig->y, x, y) == 0 || DiagonalPattern(*myboard, fig->x, fig->y, x, y) == 0){
				MakeTurn(myboard, fig, x, y);
				return 0;
			}
			break;
		case 'q': //королева
			if(LinearPattern(*myboard, fig->x, fig->y, x, y) == 0 || DiagonalPattern(*myboard, fig->x, fig->y, x, y) == 0){
				MakeTurn(myboard, fig, x, y);
				return 0;
			}
			break;
		case 'h': //конь
			if(KnightPattern(*myboard, fig->x, fig->y, x, y) == 0){
				MakeTurn(myboard, fig, x, y);
				return 0;
			}
			break;
		case 'b': //ладья
			if(LinearPattern(*myboard, fig->x, fig->y, x, y) == 0){
				MakeTurn(myboard, fig, x, y);
				return 0;
			}
			break;
		case 'w': //пешка
			if(LinearPattern(*myboard, fig->x, fig->y, x, y) == 0){
				MakeTurn(myboard, fig, x, y);
				return 0;
			}
		case 'e': //слон
			if(DiagonalPattern(*myboard, fig->x, fig->y, x, y) == 0){
				MakeTurn(myboard, fig, x, y);
				return 0;
			}
			break;
	}
	return 1;	
}