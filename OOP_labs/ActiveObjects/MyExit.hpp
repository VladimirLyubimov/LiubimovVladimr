#pragma once
#include "MyObject.hpp"

class MyExit : public MyObject{
	public:
		MyExit(int x, int y);
		virtual void Action(MyPlayer* player);
		virtual ~MyExit();
};
