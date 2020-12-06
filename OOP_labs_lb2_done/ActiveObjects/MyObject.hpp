#pragma once
#include "../Humans/MyPlayer.hpp"
#include "../Logs/LogInterface.hpp"

class MyObject{
	protected:
		MyObject();
	public:
		virtual ~MyObject();
		virtual bool operator +=(MyPlayer* player) = 0;
		virtual const char* getLogData() = 0;
};

LogInterface& operator <<(LogInterface& log, MyObject* obj);
