#pragma once
#include <iostream>
#include "../Maze/MyMaze.hpp"

class MyInterface{//класс реализующий примитивный консольный интерфейс
	private:
		char** m_matrix;
	public:
		MyInterface();
		void printMaze(MyMaze &maze, MyPlayer* player);
		int getGameCommand(int &dx, int &dy);
};		
