#include "MyPlayer.hpp"

MyPlayer::MyPlayer(int x = 1, int y = 1, int health = 100, int movepoints = 3, int damage = 20, int exp = 0, int level = 1)
	:m_x(x), m_y(y), m_health(health), m_movepoints(movepoints), m_damage(damage), m_experience(exp),m_level(level)
{	
}

MyPlayer::MyPlayer(const MyPlayer &obj){
	m_x = obj.m_x;
	m_y = obj.m_y;
	m_health = obj.m_health;
	m_movepoints = obj.m_movepoints;
	m_damage = obj.m_damage;
	m_experience = obj.m_experience;
	m_level = obj.m_level;	
}

void MyPlayer::Move(int dx, int dy){//перемешение игрока
	m_x += dx;
	m_y += dy;
	m_movepoints -= 1;
}

void MyPlayer::setHealth(int health){
	m_health += health;
}

void MyPlayer::getCoordinates(int &x, int &y){
	x = m_x;
	y = m_y;
}
