#include "MyBonus.hpp"

MyBonus::MyBonus(): MyObject(){
};

bool MyBonus::Action(MyPlayer* player){
	player->addExp(50);
	player->levelup();
	return true;
};

MyBonus::~MyBonus(){};
