#include "MyDynamite.hpp"

MyDynamite::MyDynamite(int x, int y): MyObject(x,y){
};

void MyDynamite::Action(MyPlayer* player){
	player->takeDamage(200);
};

MyDynamite::~MyDynamite(){};
