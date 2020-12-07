#include "MyObject.hpp"

MyObject::MyObject(){
};

MyObject::~MyObject(){};

LogInterface& operator <<(LogInterface& log, MyObject* obj){
	log.writeLog(obj->getLogData());
	return log;
}
