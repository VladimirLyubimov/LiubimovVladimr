#include "MyObject.hpp"

MyObject::MyObject(int x, int y){
	m_x = x;
	m_y = y;
};

MyObject& MyObject::operator +=(MyPlayer* player){
	this->Action(player);
	return *this;
}

MyObject::~MyObject(){};
