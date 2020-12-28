#pragma once
#include <iostream>
#include "../Maze/MyMaze.hpp"
#include "../Humans/Enemy.hpp"
#include <string>

class MyInterface{//класс реализующий примитивный консольный интерфейс
	private:
		char** m_matrix;
	public:
		MyInterface();
		void printMaze(MyMaze &maze, MyPlayer* player, SuperEnemy** enemies, int len);
		int getGameCommand(int &dx, int &dy);
		static::std::string getFilename();
};		
