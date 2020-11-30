#include "MyPlayer.hpp"

MyPlayer::MyPlayer(int x, int y, int health, int damage , int level, int exp, bool collected) : MyHuman(x, y, health, damage, level), m_exp(exp), m_collected(collected), m_exit(false){
};

void MyPlayer::addExp(int exp){
	m_exp += exp;
};

void MyPlayer::setCollected(){
	m_collected =  true;
};

void MyPlayer::levelup(){
	if(m_exp >= 100){
		MyHuman::levelup();
		addExp(-100);
	}
};

char MyPlayer::print(){
	return 'H';
};

bool MyPlayer::getCoollected(){
	return m_collected; 
};

void MyPlayer::setExit(){
	if (m_collected)
		m_exit =  true;
};

bool MyPlayer::getExit(){
	return m_exit;
};

int MyPlayer::getExp(){
	return m_exp;
}
