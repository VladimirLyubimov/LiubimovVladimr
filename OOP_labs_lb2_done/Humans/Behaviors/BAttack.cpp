#include "BAttack.hpp"

void BAttack::Action(MyHuman* first, MyHuman* second, int dx, int dy){
	*second += first;
}
