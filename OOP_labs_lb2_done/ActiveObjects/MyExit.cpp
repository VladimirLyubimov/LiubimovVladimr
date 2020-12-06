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

const char* MyExit::getLogData(){
	return "Exit has been reached. Game has been overed.\n";
}

MyExit::~MyExit(){};
