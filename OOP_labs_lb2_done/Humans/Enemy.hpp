#pragma once
#include <string>
#include "../Maze/MyMaze.hpp"
#include "SuperEnemy.hpp"
#include "./Behaviors/Behavior.hpp"
#include "./Behaviors/BAttack.hpp"
#include "./Behaviors/BDamage.hpp"
#include "./Behaviors/BLevel.hpp"
#include <ctime>
#include <cstdlib>

template <class T>
class Enemy: public SuperEnemy{
	private:
		T* m_behavior;
		MyCell* m_position;
	private:
		MyHuman* checkSurround(MyHuman* aim, MyMaze& maze);
	public:
		Enemy(int x, int y, int health, int damage, int level, MyMaze& maze);
		~Enemy();
		void makeTurn(MyMaze& maze);
		virtual char print();
		void setPosition(MyMaze &maze);
};

template <class T>
Enemy<T>::Enemy(int x, int y, int health, int damage, int level, MyMaze& maze) : SuperEnemy(x, y, health, damage, level){
	m_behavior = new T();
	m_position = maze.getCell(x,y);
	m_position->setIsHuman(this);
}

template <class T>
Enemy<T>::~Enemy(){
	delete m_behavior;
}

template <class T>
void Enemy<T>::setPosition(MyMaze &maze){
	int x = 0;
	int y = 0;
	this->getCoord(x, y);
	m_position = maze.getCell(x, y);
}

template <class T>
MyHuman* Enemy<T>::checkSurround(MyHuman* aim, MyMaze& maze){
	int x = 0;
	int y = 0;
	this->getCoord(x, y);
	aim = maze.getCell(x+1,y)->getIsHuman();
	if(aim)
		return aim;
		
	aim = maze.getCell(x,y+1)->getIsHuman();
	if(aim)
		return aim;
		
	aim = maze.getCell(x-1,y)->getIsHuman();
	if(aim)
		return aim;
		
	aim = maze.getCell(x,y-1)->getIsHuman();
	if(aim)
		return aim;
	
	return nullptr;
}

template <class T>
void Enemy<T>::makeTurn(MyMaze& maze){
	if(m_health <= 0)
		m_alive = false;
	if(!this->getAlive()){
		int x = 0;
		int y = 0;
		this->getCoord(x, y);
		maze.getCell(x,y)->setIsHuman(nullptr);
		this->setCoord(0,0);
		return;
	}
	
	MyHuman* aim = nullptr;
	aim = checkSurround(aim, maze);
	if(aim){
		m_behavior->Action(this, aim);
		return;
	}
	
	srand(time(NULL));
	int way = rand() % 4;	
	int x = 0;
	int y = 0;
	this->getCoord(x, y);
			
	switch(way){
		case 0:
			if(maze.getCell(x+1,y)->getPassable()){
				maze.getCell(x,y)->setIsHuman(nullptr);
				this->Move(1,0);
				maze.getCell(x+1,y)->setIsHuman(this);
				return;
			}
				
		case 1:
			if(maze.getCell(x,y+1)->getPassable()){
				maze.getCell(x,y)->setIsHuman(nullptr);
				this->Move(0,1);
				maze.getCell(x,y+1)->setIsHuman(this);
				return;
			}
					
		case 2:
			if(maze.getCell(x-1,y)->getPassable()){
				maze.getCell(x,y)->setIsHuman(nullptr);
				this->Move(-1,0);
				maze.getCell(x-1,y)->setIsHuman(this);
				return;
			}
				
		case 3:
			if(maze.getCell(x,y-1)->getPassable()){
				maze.getCell(x,y)->setIsHuman(nullptr);
				this->Move(0,-1);
				maze.getCell(x,y-1)->setIsHuman(this);
				return;
			}
					
		default:
			return;
	}
}

template <class T>
char Enemy<T>::print(){
	return 'E';
}
