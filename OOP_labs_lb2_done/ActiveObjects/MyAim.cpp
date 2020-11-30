#include "MyAim.hpp"

MyAim::MyAim(): MyObject(){
};

bool MyAim::Action(MyPlayer* player){
	player->setCollected();
	return true;
};

MyAim::~MyAim(){};
