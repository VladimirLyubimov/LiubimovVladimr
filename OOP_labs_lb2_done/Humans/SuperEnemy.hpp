#pragma once
#include "MyHuman.hpp"
#include "../Maze/MyMaze.hpp"
#include <string>
#include "../Logs/LogInterface.hpp"

class SuperEnemy: public MyHuman{
	public:
		SuperEnemy(int x, int y, int health, int damage, int level): MyHuman(x, y, health, damage, level){};
		virtual void makeTurn(MyMaze& maze) = 0;
		std::string getLogData();
		void MakeLog(LogInterface* FLog, LogInterface* CLog, SuperEnemy* LogObj);
};

LogInterface& operator <<(LogInterface& log, SuperEnemy* Obj);
