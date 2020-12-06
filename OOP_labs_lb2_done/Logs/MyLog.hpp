#pragma once

class MyLog{
	protected:
		MyLog();
		virtual ~MyLog();
	public:
		virtual void write(const char* data) = 0;
};
