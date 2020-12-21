#pragma once
#include <iostream>
#include "../Maze/MyMaze.hpp"
#include "../Humans/Enemy.hpp"

class MyInterface{//класс реализующий примитивный консольный интерфейс
	private:
		char** m_matrix;
	public:
		MyInterface();
		void printMaze(MyMaze &maze, MyPlayer* player, SuperEnemy** enemies, int len);
		int getGameCommand(int &dx, int &dy);
};		
