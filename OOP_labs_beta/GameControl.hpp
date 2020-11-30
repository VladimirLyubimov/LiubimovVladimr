#pragma once
#include "iostream"
#include "fstream"
#include "MyCell.hpp"
#include "CellStack.hpp"
#include "MyMaze.hpp"
#include "MyInterface.hpp"
#include "MyPlayer.hpp"
#include "MyGUI.hpp"
#include "PlayerControl.hpp"
#include "./ActiveObjects/MyDynamite.hpp"
#include "./ActiveObjects/MyExit.hpp"
#include "./ActiveObjects/MyBonus.hpp"
#include "./ActiveObjects/MyAim.hpp"

using namespace std;

class GameControl{
	private:
		MyMaze* m_maze;
		MyInterface m_interface;
		PlayerControl* m_hero;
		MyExit* m_finish;
		MyBonus* m_bonus;
		MyAim* m_aim;
		MyDynamite* m_dynamite;

	public:
		GameControl();
		~GameControl();
		void Execute();	
};
