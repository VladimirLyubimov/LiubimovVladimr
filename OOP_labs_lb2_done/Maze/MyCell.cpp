#include "MyCell.hpp"

MyCell::MyCell() {
    m_passable = 0;
    m_type = STATE_WALL;
    m_touched = 0;
    m_ActObj = nullptr;
    m_isHuman = nullptr;
}

MyCell::MyCell(const MyCell &cell) {//конструктор копирования
    m_passable = cell.m_passable;
    m_type = cell.m_type;
    m_touched = cell.m_touched;
    m_x = cell.m_x;
    m_y = cell.m_y;
    m_ActObj = cell.m_ActObj;
    m_isHuman = cell.m_isHuman;
}

void MyCell::setData(int set_passable, State set_type) {//установка параметров проходимости и типа клетки
    m_passable = set_passable;
    m_type = set_type;
}

void MyCell::setCoordinates(int set_x, int set_y) {//установка координат клетки
    m_x = set_x;
    m_y = set_y;
}

void MyCell::getCoordinates(int &get_x, int &get_y) {
    get_x = this->m_x;
    get_y = this->m_y;
}

char MyCell::getPrintChar(){
    if (m_type == STATE_WALL) {
        return '@';
    }
    if (m_type == STATE_GROUND) {
        return '1';
    }
    if (m_type == STATE_START) {
        return 'S';
    }
    if (m_type == STATE_FINISH) {
        return 'F';
    }    
    if (m_type == STATE_DYNAMITE) {
        return 'D';
    }
    if (m_type == STATE_BONUS) {
        return 'B';
    }
    if (m_type == STATE_AIM) {
        return 'A';
    }
    return '!';
}

void MyCell::setAttendance() {//установка параметра посещённости
    m_touched = 1;
}

int MyCell::getAttendance() {//получение значения параметра посещённости
    return this->m_touched;
}

int MyCell::getPassable(){
	return m_passable;
}

State MyCell::getType(){
    return m_type;
}

void MyCell::setActObj(MyObject* Obj){
	m_ActObj = Obj;
}
MyObject* MyCell::getActObj(){
	return m_ActObj; 
}

void MyCell::setIsHuman(MyHuman* human) {
    m_isHuman = human;
}

MyHuman* MyCell::getIsHuman() {
    return m_isHuman;
}

MyCell::~MyCell() {
}
		
