#pragma once
#include "iostream"
#include "fstream"
#include "./Maze/MyCell.hpp"
#include "./Maze/CellStack.hpp"
#include "./Maze/MyMaze.hpp"
#include "./Interface/MyInterface.hpp"
#include "./Humans/MyPlayer.hpp"
#include "./Humans/PlayerControl.hpp"
#include "./ActiveObjects/MyDynamite.hpp"
#include "./ActiveObjects/MyExit.hpp"
#include "./ActiveObjects/MyBonus.hpp"
#include "./ActiveObjects/MyAim.hpp"
#include "./Logs/LogInterface.hpp"
#include "./Logs/FileLog.hpp"
#include "./Logs/ConsolLog.hpp"

using namespace std;

class GameControl{
	private:
		MyMaze* m_maze;
		MyInterface m_interface;
		PlayerControl* m_hero;
		MyObject* m_finish;
		MyObject* m_bonus;
		MyObject* m_aim;
		MyObject* m_dynamite;

	public:
		GameControl();
		~GameControl();
		void Execute();	
};
