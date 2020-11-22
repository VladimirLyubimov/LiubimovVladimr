#include "MyDynamite.hpp"

MyDynamite::MyDynamite(int x, int y): MyObject(x,y){
	//m_type = STATE_DYNAMITE;
};

void MyDynamite::Action(MyPlayer* player){
	player->takeDamage(200);
	//cell.setData(1, STATE_GROUND);
};

MyDynamite::~MyDynamite(){};
