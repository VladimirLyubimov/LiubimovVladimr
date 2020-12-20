#pragma once
#include "Behavior.hpp"

class BMove: public Behavior{
	public:
		virtual void Action(MyHuman* first, MyHuman* second, int dx, int dy);
};
