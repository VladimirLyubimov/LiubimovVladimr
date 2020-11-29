#pragma once
#include "../MyPlayer.hpp"

class MyObject{
	protected:
		int m_x;
		int m_y;
	protected:
		MyObject(int x, int y);
	public:
		virtual void Action(MyPlayer* player) = 0;
		virtual ~MyObject();
		MyObject& operator +=(MyPlayer* player);
};
