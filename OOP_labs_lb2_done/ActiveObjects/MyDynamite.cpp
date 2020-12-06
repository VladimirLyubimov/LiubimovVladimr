#include "MyDynamite.hpp"

MyDynamite::MyDynamite(): MyObject(){
};

bool MyDynamite::operator +=(MyPlayer* player){
	player->takeDamage(200);
	return true;
}

const char* MyDynamite::getLogData(){
	return "Dynamite has explpoded. Hero has take 200 damage.\n";
}

MyDynamite::~MyDynamite(){};
