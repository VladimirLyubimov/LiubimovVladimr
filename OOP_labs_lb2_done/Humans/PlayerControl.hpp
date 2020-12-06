#pragma once
#include "MyPlayer.hpp"
#include "../Maze/MyMaze.hpp"
#include "../ActiveObjects/MyObject.hpp"
#include "iostream"
#include "../Logs/LogInterface.hpp"

class PlayerControl{
	private:
		MyPlayer* m_hero;
		MyCell* m_position;
	public:
		PlayerControl(int x, int y, MyMaze& maze);
		~PlayerControl();
		MyPlayer* getPlayer();
		void showStats();
		void setPosition(MyMaze &maze);
		int Move(MyMaze& maze, int dx, int dy, LogInterface& MazeLog);
};
