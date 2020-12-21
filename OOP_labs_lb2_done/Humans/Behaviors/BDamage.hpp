#pragma once
#include "Behavior.hpp"

class BDamage: public Behavior{
	public:
		virtual void Action(MyHuman* attacker, MyHuman* aim);
};
