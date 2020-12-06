#pragma once
#include "FileLog.hpp"
#include "ConsolLog.hpp"

class LogInterface{
	private:
		FileLog* m_filelog;
		ConsolLog* m_consollog;
	public:
		LogInterface(FileLog* file, ConsolLog* consol);
		~LogInterface();
		void writeLog(const char* data);
};
