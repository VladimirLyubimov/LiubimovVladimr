#pragma once
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
		void makeTurn(MyHuman* first, MyHuman* second, int dx, int dy);
		virtual char print(); 
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
void Enemy<T>::makeTurn(MyHuman* first, MyHuman* second, int dx, int dy){
	m_behavior->Action(first, second, dx, dy);
}

template <class T>
char Enemy<T>::print(){
	return 'E';
}
