#include "MyAim.hpp"

MyAim::MyAim(): MyObject(){
};

bool MyAim::operator +=(MyPlayer* player){
	player->setCollected();
	return true;
}

const char* MyAim::getLogData(){
	return "Aim has been succssefully collected. Exit has been unlocked.\n";
}

MyAim::~MyAim(){};
