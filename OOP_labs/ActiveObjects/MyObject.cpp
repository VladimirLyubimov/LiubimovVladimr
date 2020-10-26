#include "MyObject.hpp"

MyObject::MyObject(int x, int y){
	m_x = x;
	m_y = y;
	m_type = STATE_UNDEFOBJ;
};

void MyObject::setInMaze(MyCell &cell){
	cell.setData(1, m_type);
};
