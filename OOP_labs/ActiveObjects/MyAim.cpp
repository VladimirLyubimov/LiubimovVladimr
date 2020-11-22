#include "MyAim.hpp"

MyAim::MyAim(int x, int y): MyObject(x, y){
};

void MyAim::Action(MyPlayer* player){
	player->setCollected();
};

MyAim::~MyAim(){};
