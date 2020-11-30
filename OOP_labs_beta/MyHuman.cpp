#include "MyHuman.hpp"

MyHuman::MyHuman(int x, int y, int health, int damage, int level, int movepoints, int armor): m_x(x), m_y(y), m_health(health), m_damage(damage), m_level(level), m_movepoints(movepoints), m_armor(armor){
};

void MyHuman::Move(int dx, int dy){
	m_x += dx;
	m_y += dy;
	m_movepoints -= 1;
};

void MyHuman::takeDamage(int damage){
	m_health -= damage;
};

int MyHuman::CalcDamage(int target_level, int target_armor, int target_health){
	int dlev = m_level - target_level;
	double modify = exp(static_cast<double>(dlev))*10;
	int damage = m_damage * static_cast<int>(modify) * m_level - target_armor + target_health/20;
	return damage;	
};

void MyHuman::changeDamage(int ddamage){
	m_damage += ddamage;
};

void MyHuman::changeLevel(int dlevel){
	m_level += dlevel;
};

void MyHuman::changeMovepoints(int dmovepoints){
	m_movepoints += dmovepoints;
};

void MyHuman::changeArmor(int darmor){
	m_armor += darmor;
};

void MyHuman::levelup(){
	changeDamage(m_damage/2);
	changeLevel(1);
	changeMovepoints(1);
	takeDamage((-1)*m_health);
	changeArmor(m_armor);
}

void MyHuman::setCoord(int x, int y){
	m_x = x;
	m_y = y;
};

void MyHuman::getCoord(int &x, int &y){
	x = m_x;
	y = m_y;
};

int MyHuman::getHealth(){
	return m_health;
}

int MyHuman::getLevel(){
	return m_level;
}
