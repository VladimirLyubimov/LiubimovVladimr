#include "LogInterface.hpp"

LogInterface::LogInterface(MyLog* log): m_log(log){
}

LogInterface::~LogInterface(){
}

void LogInterface::writeLog(string data){
	if(m_log)
		m_log->write(data);
}
