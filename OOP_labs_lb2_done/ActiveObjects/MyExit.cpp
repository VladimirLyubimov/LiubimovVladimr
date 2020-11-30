#include "MyExit.hpp"

MyExit::MyExit(): MyObject(){
};

bool MyExit::Action(MyPlayer* player){
	if (player->getCoollected()){
		player->setExit();
		return true;
	}
	return false;
};

MyExit::~MyExit(){};
