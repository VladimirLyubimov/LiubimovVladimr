#pragma once
#include "../Humans/MyPlayer.hpp"
#include "../Logs/LogInterface.hpp"
#include <string>

class MyObject{
	protected:
		MyObject();
	public:
		virtual ~MyObject();
		virtual bool operator +=(MyPlayer* player) = 0;
		virtual std::string getLogData() = 0;
};

LogInterface& operator <<(LogInterface& log, MyObject* obj);
