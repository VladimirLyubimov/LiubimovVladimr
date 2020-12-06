#pragma once
#include "MyObject.hpp"

class MyExit : public MyObject{
	public:
		MyExit();
		virtual bool operator +=(MyPlayer* player);
		virtual LogInterface& operator <<(LogInterface& log);
		virtual ~MyExit();
};
