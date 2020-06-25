#include "chess_board.h"

int isCellEmpty(cell mycell){
	return mycell.isEmpty == 1;
}

void init(cboard* myboard){
	myboard->board = (cell**)malloc(8*sizeof(cell*));
	int i = 0;
	int j;
	for(i; i < 8; i++){
		j = 0;
		myboard->board[i] = (cell*)malloc(8*sizeof(cell));
		for(j; j < 8; j++){
			myboard->board[i][j].isEmpty = 1;
			myboard->board[i][j].fig_num = -1;
			myboard->board[i][j].color = 'b';
			if((i%2 == 0 && j%2 == 0) || (j%2 == 1 && 1%2 == 1))
				myboard->board[i][j].color = 'w';
		}
	}
	//return myboard;
}

void myFree(cboard* myboard){
	int i = 0;
	for(i; i < 8; i++)
		free(myboard->board[i]);
	free(myboard->board);
}