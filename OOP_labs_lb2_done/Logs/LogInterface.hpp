#pragma once
#include "FileLog.hpp"
#include "ConsolLog.hpp"

class LogInterface{
	private:
		MyLog* m_log;
	public:
		LogInterface(MyLog* log);
		~LogInterface();
		void writeLog(string data);
};
