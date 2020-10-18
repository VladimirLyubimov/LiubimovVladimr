#include "MyPlayer.hpp"

MyPlayer::MyPlayer(int x, int y, int health, int damage , int level, int movepoints, int armor, int exp) : MyHuman(x, y, health, damage, level, movepoints, armor), m_exp(exp){
};

void MyPlayer::addExp(int exp){
	m_exp += exp;
};

void MyPlayer::levelup(){
	MyHuman::levelup();
	addExp(-100);
};

char MyPlayer::print(){
	return 'H';
};
