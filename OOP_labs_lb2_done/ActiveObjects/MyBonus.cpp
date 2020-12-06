#include "MyBonus.hpp"

MyBonus::MyBonus(): MyObject(){
};

bool MyBonus::operator +=(MyPlayer* player){
	player->addExp(50);
	player->levelup();
	return true;
}

LogInterface& MyBonus::operator <<(LogInterface& log){
	log.writeLog("Bonus has been successfully collected. Hero has been given 50 experience.\n");
	return log;
}

MyBonus::~MyBonus(){};
