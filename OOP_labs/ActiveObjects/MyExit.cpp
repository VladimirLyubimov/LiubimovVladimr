#include "MyExit.hpp"

MyExit::MyExit(int x, int y): MyObject(x, y){
};

void MyExit::Action(MyPlayer* player){
	player->setExit();
};

MyExit::~MyExit(){};
