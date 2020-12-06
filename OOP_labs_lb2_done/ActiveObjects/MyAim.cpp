#include "MyAim.hpp"

MyAim::MyAim(): MyObject(){
};

bool MyAim::operator +=(MyPlayer* player){
	player->setCollected();
	return true;
}

LogInterface& MyAim::operator <<(LogInterface& log){
	log.writeLog("Aim has been successfully collected.\n");
	return log;
}

MyAim::~MyAim(){};
