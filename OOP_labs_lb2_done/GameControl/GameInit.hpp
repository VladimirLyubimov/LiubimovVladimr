#pragma once
#include "iostream"
#include "fstream"
#include "../Maze/MyMaze.hpp"
#include "../ActiveObjects/MyDynamite.hpp"
#include "../ActiveObjects/MyExit.hpp"
#include "../ActiveObjects/MyBonus.hpp"
#include "../ActiveObjects/MyAim.hpp"
#include "PlayGroundStruct.hpp"
#include "Save.hpp"
#include "Load.hpp"

class GameInit{
	public:
		//void NewGameFromOld
		static void InitGame(PlayGround& field);
		static void EndGame(PlayGround& field);
};
