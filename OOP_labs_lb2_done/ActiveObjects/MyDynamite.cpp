#include "MyDynamite.hpp"

MyDynamite::MyDynamite(): MyObject(){
};

bool MyDynamite::Action(MyPlayer* player){
	player->takeDamage(200);
	return true;
};

MyDynamite::~MyDynamite(){};
