#include "FileLog.hpp"

FileLog::FileLog(const char* filename){
	m_file = new ofstream(filename);
}

FileLog::~FileLog(){
	m_file->close();
	delete m_file;
}

void FileLog::write(string data){
	if(m_file->is_open())
		*m_file << data;
}
