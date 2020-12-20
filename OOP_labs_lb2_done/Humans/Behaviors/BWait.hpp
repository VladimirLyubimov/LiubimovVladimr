#pragma once
#include "Behavior.hpp"
#include <ctime>
#include <cstdlib>

class BWait: public Behavior{
	public:
		virtual void Action(MyHuman* first, MyHuman* second, int dx, int dy);
};
