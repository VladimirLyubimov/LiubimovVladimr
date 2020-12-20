#pragma once
#include "Enemy.hpp"
#include "../Maze/MyMaze.hpp"
#include "./Behaviors/Behavior.hpp"
#include "./Behaviors/BAttack.hpp"
#include "./Behaviors/BMove.hpp"
#include "./Behaviors/BWait.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>

class EnemyControl{
	public:
		Enemy<Behavior>* m_enemy;
		MyCell* m_position;
		Behavior* m_beh;
	private:
		MyHuman* checkSurround(MyHuman* aim, MyMaze& maze);
	public:
		EnemyControl(int x, int y, MyMaze& maze);
		~EnemyControl();
		Enemy<Behavior>* getPlayer();
		void setPosition(MyMaze &maze);
		void makeTurn(MyMaze& maze);
};
