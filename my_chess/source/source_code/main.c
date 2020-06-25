#include <stdio.h>
#include "pngio.h"
#include "draw_png.h"
#include "draw_grid.h"
#include "chess_board.h"
#include "chess_figures.h"
#include "draw_figures.h"

int main(){
	png image;
	color white = {255, 255, 255};
	color black = {0, 0, 0};
	color fig_white = {255, 180, 180};
	color fig_black = {70, 70, 70};
	figure fig ={0,0,0,'q','w'};
	cboard brd;
	init(&brd);
	//printf("%d\n", brd.board[0][0].fig_num);
	ReadFile("france.png", &image);
	DrawTwoColorSquareGrid(&image, white, black, 8);
	brd.board[0][0].isEmpty = 0;
	brd.board[0][0].fig_num = fig.num;
	DrawQueen(&image, fig.x, fig.y, fig_black);
	printf("%d\n", OneTurn(&brd, &fig, 4, 0));
	//DrawQueen(&image, 1, 0, fig_white);
	//DrawQueen(&image, 7, 7, fig_black);
	DrawQueen(&image, fig.x, fig.y, fig_black);
	OutputImage("res.png", &image);
	return 0;
}