#pragma once
#include "MyPlayer.hpp"
#include "MyMaze.hpp"
#include "./ActiveObjects/MyObject.hpp"
#include "iostream"

class ControlPlayer{
	private:
		MyPlayer* m_hero;
		MyCell* m_position;
	public:
		ControlPlayer(int x, int y, MyMaze& maze);
		ControlPlayer& operator +=(MyMaze& maze);//взаимодействие с клеткой поля
		~ControlPlayer();
		void showStats();
		void setPosition(MyMaze &maze);
		int Move(MyMaze& maze, int dx, int dy);
};
