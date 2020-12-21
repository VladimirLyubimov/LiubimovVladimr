#include "BAttack.hpp"

void BAttack::Action(MyHuman* attacker, MyHuman* aim){
	*attacker += aim;
}
