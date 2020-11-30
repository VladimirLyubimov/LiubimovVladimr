#pragma once
#include "MyObject.hpp"

class MyAim : public MyObject{
	public:
		MyAim();
		virtual bool Action(MyPlayer* player);
		virtual ~MyAim();
};
