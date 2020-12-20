#pragma once
#include "../Logs/LogInterface.hpp"
#include <string>
#include "MyHuman.hpp"
#include "./Behaviors/Behavior.hpp"

template <class T>
class Enemy: public MyHuman{
	private:
		T* m_behavior;
	public:
		Enemy(int x, int y, int health, int damage, int level, T* behavior);
		~Enemy();
		void setBehavior(T* behavior);
		void makeTurn(MyHuman* first, int dx, int dy);
		virtual char print();
		//LogInterface& operator <<(LogInterface& log);
		std::string getLogData();
};

template <class T>
Enemy<T>::Enemy(int x, int y, int health, int damage, int level, T* behavior) : MyHuman(x, y, health, damage, level), m_behavior(behavior){
}

template <class T>
Enemy<T>::~Enemy(){}

template <class T>
void Enemy<T>::setBehavior(T* behavior){
	m_behavior = nullptr;
	m_behavior = behavior;
}

template <class T>
void Enemy<T>::makeTurn(MyHuman* first, int dx, int dy){
	m_behavior->Action(first, this, dx, dy);
}

template <class T>
char Enemy<T>::print(){
	return 'E';
}

template <class T>
std::string Enemy<T>::getLogData(){
	if(this->m_alive){
		std::string data("Enemy position is (");
		int x = 0;
		int y = 0;
		this->getCoord(x,y);
		data += std::to_string(x) + ";" + std::to_string(y) + "). ";
		data += "Health = " + std::to_string(this->getHealth()) + ". ";
		data += "Level = " + std::to_string(this->getLevel()) + ". ";
		
		if(this->m_hit){
			data += " Attack has completed!";
			m_hit = false;
		}
		if(this->m_kill){
			data += " Target has been destroyed!";
			m_kill = false;
		}
		if(this->getHealth() <= 0)
			data += " Health isn't under 0. Died!";
		data += "\n";
		return data;
	}
	
	return "";
}

template <class T>
LogInterface& operator <<(LogInterface& log, Enemy<T>* Obj){
	log.writeLog(Obj->getLogData());
	return log;
}
