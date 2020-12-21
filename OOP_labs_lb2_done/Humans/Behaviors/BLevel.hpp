#pragma once
#include "Behavior.hpp"
#include <ctime>
#include <cstdlib>

class BLevel: public Behavior{
	public:
		virtual void Action(MyHuman* attacker, MyHuman* aim);
};
