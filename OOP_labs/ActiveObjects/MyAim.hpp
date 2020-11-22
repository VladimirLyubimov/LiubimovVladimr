#pragma once
#include "MyObject.hpp"

class MyAim : MyObject{
	public:
		MyAim(int x, int y);
		virtual void Action(MyPlayer* player);
		virtual ~MyAim();
};
