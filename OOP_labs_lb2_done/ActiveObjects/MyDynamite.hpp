#pragma once
#include "MyObject.hpp"

class MyDynamite : public MyObject{
	public:
		MyDynamite();
		virtual bool operator +=(MyPlayer* player);
		virtual const char* getLogData();
		virtual ~MyDynamite();
};
