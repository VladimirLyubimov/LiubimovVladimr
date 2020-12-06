#pragma once
#include "MyLog.hpp"
#include <fstream>
#include <iostream>

using namespace std;

class FileLog: public MyLog{
	private:
		ofstream* m_file;
	public:
		FileLog(const char* filename);
		~FileLog();
		virtual void write(string data);
};
