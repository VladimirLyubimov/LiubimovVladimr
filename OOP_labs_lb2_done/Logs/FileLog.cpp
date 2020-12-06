#include "FileLog.hpp"

FileLog::FileLog(const char* filename){
	m_file = new ofstream();
	m_file->open(filename);
}

FileLog::~FileLog(){
	m_file->close();
	delete m_file;
}

void FileLog::write(const char* data){
	if(m_file)
		*m_file << data;
}
