#pragma once
//#include "../MyCell.hpp"
#include "../MyPlayer.hpp"

class MyObject{
	protected:
		int m_x;
		int m_y;
		//State m_type;
	protected:
		MyObject(int x, int y);
		//void setInMaze(MyCell &cell);
	public:
		virtual void Action(MyPlayer* player) = 0;
		virtual ~MyObject();
};
