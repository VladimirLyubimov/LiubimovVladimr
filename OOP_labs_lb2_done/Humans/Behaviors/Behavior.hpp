#pragma once
#include "../MyHuman.hpp"

class Behavior{
	public:
		virtual void Action(MyHuman* attacker, MyHuman* aim) = 0;
};
