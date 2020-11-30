#include "MyDynamite.hpp"

MyDynamite::MyDynamite(): MyObject(){
};

bool MyDynamite::operator +=(MyPlayer* player){
	player->takeDamage(200);
	return true;
}
MyDynamite::~MyDynamite(){};
