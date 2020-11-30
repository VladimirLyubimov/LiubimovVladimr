#pragma once
#include "../Humans/MyPlayer.hpp"

class MyObject{
	protected:
		MyObject();
	public:
		virtual ~MyObject();
		virtual bool operator +=(MyPlayer* player) = 0;
};
