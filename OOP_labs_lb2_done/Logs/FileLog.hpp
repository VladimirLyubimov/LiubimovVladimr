#pragma once
#include "MyLog.hpp"
#include <fstream>

using namespace std;

class FileLog: public MyLog{
	private:
		ofstream* m_file;
	public:
		FileLog(const char* filename);
		~FileLog();
		virtual void write(const char* data);
};
