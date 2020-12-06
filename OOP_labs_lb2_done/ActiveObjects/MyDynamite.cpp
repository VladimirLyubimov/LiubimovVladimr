#include "MyDynamite.hpp"

MyDynamite::MyDynamite(): MyObject(){
};

bool MyDynamite::operator +=(MyPlayer* player){
	player->takeDamage(200);
	return true;
}

LogInterface& MyDynamite::operator <<(LogInterface& log){
	log.writeLog("Dynamite has explpoded. Hero has take 200 damage.\n");
	return log;
}

MyDynamite::~MyDynamite(){};
