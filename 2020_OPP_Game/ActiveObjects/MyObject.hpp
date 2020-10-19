#pragma once
#include "../MyCell.hpp"
#include "../MyPlayer.hpp"

class MyObject{
	protected:
		int m_x;
		int m_y;
		State m_type;
	public:
		MyObject(int x, int y);
		virtual void Action(MyPlayer* player, MyCell &cell) = 0;
		void setInMaze(MyCell &cell);
};
