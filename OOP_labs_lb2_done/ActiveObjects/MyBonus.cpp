#include "MyBonus.hpp"

MyBonus::MyBonus(): MyObject(){
};

bool MyBonus::operator +=(MyPlayer* player){
	player->addExp(50);
	player->levelup();
	return true;
}

MyBonus::~MyBonus(){};
