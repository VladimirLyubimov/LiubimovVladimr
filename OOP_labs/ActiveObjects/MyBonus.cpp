#include "MyBonus.hpp"

MyBonus::MyBonus(int x, int y): MyObject(x, y){
};

void MyBonus::Action(MyPlayer* player){
	player->addExp(50);
};

MyBonus::~MyBonus(){};
