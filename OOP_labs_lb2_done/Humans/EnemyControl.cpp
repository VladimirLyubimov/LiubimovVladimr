#include "EnemyControl.hpp"

EnemyControl::EnemyControl(int x, int y, MyMaze& maze){
	m_beh = new BMove();
	m_enemy = new Enemy<Behavior>(x, y, 800, 8, 1, m_beh);
	m_position = maze.getCell(x,y);
}

EnemyControl::~EnemyControl(){
	delete m_enemy;
	delete m_beh;
}

Enemy<Behavior>* EnemyControl::getPlayer(){
	return m_enemy;
}

void EnemyControl::setPosition(MyMaze &maze){
	int x = 0;
	int y = 0;
	m_enemy->getCoord(x, y);
	m_position = maze.getCell(x, y);
}

MyHuman* EnemyControl::checkSurround(){}

void EnemyControl::makeTurn(){	
}
