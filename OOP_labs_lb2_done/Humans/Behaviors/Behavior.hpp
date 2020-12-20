#pragma once
#include "../MyHuman.hpp"

class Behavior{
	public:
		virtual void Action(MyHuman* first, MyHuman* second, int dx, int dy) = 0;
};
