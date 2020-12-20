#pragma once
#include "Enemy.hpp"
#include "../Maze/MyMaze.hpp"
#include "./Behaviors/Behavior.hpp"
#include "./Behaviors/BAttack.hpp"
#include "./Behaviors/BMove.hpp"
#include "./Behaviors/BWait.hpp"
#include <ctime>
#include <cstdlib>

class EnemyControl{
	private:
		Enemy<Behavior>* m_enemy;
		MyCell* m_position;
		Behavior* m_beh;
	private:
		MyHuman* checkSurround();
	public:
		EnemyControl(int x, int y, MyMaze& maze);
		~EnemyControl();
		Enemy<Behavior>* getPlayer();
		void setPosition(MyMaze &maze);
		void makeTurn();
};
