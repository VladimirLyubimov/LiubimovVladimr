#pragma once
#include "MyPlayer.hpp"
#include "MyMaze.hpp"
#include "./ActiveObjects/MyObject.hpp"

class ControlPlayer{
	public:
		MyPlayer* m_hero;
		MyCell* m_position;
	public:
		ControlPlayer(int x, int y, MyMaze& maze);
		ControlPlayer& operator +=(MyMaze& maze);//взаимодействие с клеткой поля
		void setPosition(MyMaze &maze);
		~ControlPlayer();
};
