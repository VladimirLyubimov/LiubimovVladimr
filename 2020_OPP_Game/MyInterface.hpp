#pragma once
#include <iostream>
#include "MyMaze.hpp"

class MyInterface{//класс реализующий примитивный консольный интерфейс
	public:
		void getStartOfGenerationCoordinates(int &x, int &y);//получает координаты точки старта генерации с консоли
		void getMazeSize(int &x, int &y);//получение линейных размеров лабиринта
		void getStartAndFinish(int &xs, int &ys, int &xf, int &yf);//получает точки старта и финиша
		void printMaze(MyMaze &maze);
};		
