#include "ConsolLog.hpp"

ConsolLog::ConsolLog(){
}

ConsolLog::~ConsolLog(){
}

void ConsolLog::write(const char* data){
	cout << data;
}
