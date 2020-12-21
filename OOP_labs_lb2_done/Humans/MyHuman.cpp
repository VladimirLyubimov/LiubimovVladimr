#include "MyHuman.hpp"

MyHuman::MyHuman(int x, int y, int health, int damage, int level): m_x(x), m_y(y), m_health(health), m_base_health(health), m_damage(damage), m_level(level), m_alive(true){
};

void MyHuman::Move(int dx, int dy){
	m_x += dx;
	m_y += dy;
};

void MyHuman::takeDamage(int damage){
	m_health -= damage;
};

int MyHuman::CalcDamage(int target_level, int target_health){
	int dlev = m_level - target_level;
	double modify = exp(static_cast<double>(dlev))*10;
	int damage = m_damage * static_cast<int>(modify) * m_level + target_health/20;
	return damage;	
};

void MyHuman::changeDamage(int ddamage){
	m_damage += ddamage;
};

void MyHuman::changeLevel(int dlevel){
	m_level += dlevel;
};


void MyHuman::levelup(){
	changeDamage(m_damage/2);
	changeLevel(1);
	m_base_health *= 2;
	m_health = m_base_health; 
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

int MyHuman::getBaseHealth(){
	return m_base_health;
}

int MyHuman::getLevel(){
	return m_level;
}

bool MyHuman::getAlive(){
	return m_alive;
}

int MyHuman::getDamage(){
	return m_damage;
}

MyHuman& MyHuman::operator +=(MyHuman* human){
	int damage;
	damage = this->CalcDamage(human->getLevel(), human->getBaseHealth());
	human->takeDamage(damage);
	this->m_inter = true;
	if(human->m_health <= 0){
		human->m_alive = false;
		this->m_kill = true;
	}
	return *this;
}

MyHuman& MyHuman::operator -=(MyHuman* human){
	if(human->getDamage() > 5){
		human->changeDamage(-1);
		this->m_inter = true;
	}
	return *this;
}

MyHuman& MyHuman::operator *=(MyHuman* human){
	if(human->getLevel() > 1){
		human->changeLevel(-1);
		this->m_inter = true;
	}
	return *this;
}
