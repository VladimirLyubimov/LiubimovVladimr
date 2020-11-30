#pragma once
#include "MyObject.hpp"

class MyExit : public MyObject{
	public:
		MyExit();
		virtual bool Action(MyPlayer* player);
		virtual ~MyExit();
};
