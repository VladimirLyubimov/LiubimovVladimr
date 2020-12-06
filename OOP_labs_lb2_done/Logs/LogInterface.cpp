#include "LogInterface.hpp"

LogInterface::LogInterface(FileLog* file, ConsolLog* consol): m_filelog(file), m_consollog(consol){
}

LogInterface::~LogInterface(){
}

void LogInterface::writeLog(const char* data){
	if(m_filelog)
		m_filelog->write(data);
	if(m_consollog)
		m_consollog->write(data);
}
