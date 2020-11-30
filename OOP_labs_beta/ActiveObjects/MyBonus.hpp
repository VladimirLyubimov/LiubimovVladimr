#pragma once
#include "MyObject.hpp"

class MyBonus : public MyObject{
	public:
		MyBonus();
		virtual bool Action(MyPlayer* player);
		virtual ~MyBonus();
};
