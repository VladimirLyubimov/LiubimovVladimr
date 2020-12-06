#pragma once
#include "MyLog.hpp"
#include <iostream>

using namespace std;

class ConsolLog: public MyLog{
	public:
		ConsolLog();
		~ConsolLog();
		virtual void write(string data);
};
