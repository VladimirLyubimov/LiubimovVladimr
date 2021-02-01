#pragma once
#include "MyPlayer.hpp"
#include "../Maze/MyMaze.hpp"
#include "../ActiveObjects/MyObject.hpp"
#include "../Logs/LogInterface.hpp"

class PlayerControl{
	private:
		MyPlayer* m_hero;
		MyCell* m_position;
	public:
		PlayerControl(int x, int y, MyMaze& maze, int health = 1000, int damage = 10, int level = 1, int exp = 0, bool collected = false);
		~PlayerControl();
		MyPlayer* getPlayer();
		void setPosition(MyMaze &maze);
		int Move(MyMaze& maze, int dx, int dy, LogInterface* FLog, LogInterface* CLog);
		template <class T>
		void MakeLog(LogInterface* FLog, LogInterface* CLog, T* LogObj);
};
