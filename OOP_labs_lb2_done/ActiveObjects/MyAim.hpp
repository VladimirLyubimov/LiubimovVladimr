#pragma once
#include "MyObject.hpp"

class MyAim : public MyObject{
	public:
		MyAim();
		virtual bool operator +=(MyPlayer* player);
		virtual ~MyAim();
		virtual std::string getLogData();
};
