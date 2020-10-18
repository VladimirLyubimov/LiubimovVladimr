#pragma once
#include <iostream>

using namespace std;

enum State {STATE_GROUND, STATE_WALL, STATE_START, STATE_FINISH};

class MyCell{//класс клетки
    private:
        int m_passable;//проходимость клетки
        State m_type;//её вид (стена, обычная клетка и тд.)
        int m_touched;//посещенали клетка при генерации лабиринта
        int m_x;
        int m_y;
    public:
    	MyCell();
    	MyCell(const MyCell &cell);
    	void setData(int set_passable, State set_type);
    	void setCoordinates(int set_x, int set_y);
    	void getCoordinates(int &get_x, int &get_y);
    	char getPrintChar();
    	void setAttendance();
    	int getAttendance();
    	int getPassable();
    	State getType();
    	~MyCell();
};
