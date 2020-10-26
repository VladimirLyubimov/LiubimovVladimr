#pragma once
#include "MyObject.hpp"

class MyDynamite : public MyObject{
	public:
		MyDynamite(int x, int y);
		virtual void Action(MyPlayer* player, MyCell &cell);
};
