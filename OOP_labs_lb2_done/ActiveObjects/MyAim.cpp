#include "MyAim.hpp"

MyAim::MyAim(): MyObject(){
};

bool MyAim::operator +=(MyPlayer* player){
	player->setCollected();
	return true;
}

MyAim::~MyAim(){};
