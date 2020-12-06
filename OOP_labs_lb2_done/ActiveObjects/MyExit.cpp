#include "MyExit.hpp"

MyExit::MyExit(): MyObject(){
};

bool MyExit::operator +=(MyPlayer* player){
	if (player->getCoollected()){
		player->setExit();
		return true;
	}
	return false;
}

LogInterface& MyExit::operator <<(LogInterface& log){
	log.writeLog("Exit has been reached. Game has been overed.\n");
	return log;
}

MyExit::~MyExit(){};
