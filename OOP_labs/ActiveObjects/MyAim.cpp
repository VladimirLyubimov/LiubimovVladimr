#include "MyAim.hpp"

MyAim::MyAim(int x, int y): MyObject(x, y){
	//m_type = STATE_AIM;
};

void MyAim::Action(MyPlayer* player){
	player->setCollected();
	//cell.setData(1, STATE_GROUND);
};

MyAim::~MyAim(){};
