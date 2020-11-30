#pragma once
#include "../Humans/MyPlayer.hpp"

class MyObject{
	protected:
		MyObject();
	public:
		virtual bool Action(MyPlayer* player) = 0;
		virtual ~MyObject();
		bool operator +=(MyPlayer* player);
};
