#include "MyCell.hpp"

MyCell::MyCell() {
    m_passable = 0;
    m_type = STATE_WALL;
    m_touched = 0;
}

MyCell::MyCell(const MyCell &cell) {//конструктор копирования
    m_passable = cell.m_passable;
    m_type = cell.m_type;
    m_touched = cell.m_touched;
    m_x = cell.m_x;
    m_y = cell.m_y;
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

void MyCell::print() {
    if (m_type == STATE_WALL) {
        cout << "@";
        return;
    }
    if (m_type == STATE_GROUND) {
        cout << " ";
        return;
    }
    if (m_type == STATE_START) {
        cout << "S";
        return;
    }
    if (m_type == STATE_FINISH) {
        cout << "F";
        return;
    }
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

MyCell::~MyCell() {
}
		
