#pragma once
#include <iostream>
#include "MyMaze.hpp"

class MyInterface{//класс реализующий примитивный консольный интерфейс
	private:
		char** m_matrix;
	public:
		MyInterface();
		void getStartOfGenerationCoordinates(int &x, int &y);//получает координаты точки старта генерации с консоли
		void getMazeSize(int &x, int &y);//получение линейных размеров лабиринта
		void getStartAndFinish(int &xs, int &ys, int &xf, int &yf);//получает точки старта и финиша
		void getMove(int &dx, int &dy);
		void printMaze(MyMaze &maze, MyPlayer* player);
};		
