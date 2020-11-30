#pragma once
#include "MyObject.hpp"

class MyDynamite : public MyObject{
	public:
		MyDynamite();
		virtual bool Action(MyPlayer* player);
		virtual ~MyDynamite();
};
