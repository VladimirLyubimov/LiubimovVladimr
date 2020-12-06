#include "MyBonus.hpp"

MyBonus::MyBonus(): MyObject(){
};

bool MyBonus::operator +=(MyPlayer* player){
	player->addExp(50);
	player->levelup();
	return true;
}

const char* MyBonus::getLogData(){
	return "Bonus has been successfully collected. Hero has been given 50 experience.\n";
}

MyBonus::~MyBonus(){};
