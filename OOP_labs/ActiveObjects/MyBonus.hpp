#pragma once
#include "MyObject.hpp"

class MyBonus : public MyObject{
	public:
		MyBonus(int x, int y);
		virtual void Action(MyPlayer* player);
		virtual ~MyBonus();
};
