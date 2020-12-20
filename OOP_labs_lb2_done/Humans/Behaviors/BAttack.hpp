#pragma once
#include "Behavior.hpp"

class BAttack: public Behavior{
	public:
		virtual void Action(MyHuman* first, MyHuman* second, int dx, int dy);
};
