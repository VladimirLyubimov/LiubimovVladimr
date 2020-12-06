#pragma once
#include <string>

class MyLog{
	protected:
		MyLog();
		virtual ~MyLog();
	public:
		virtual void write(std::string data) = 0;
};
