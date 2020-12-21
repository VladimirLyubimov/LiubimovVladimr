#include "BDamage.hpp"

void BDamage::Action(MyHuman* attacker, MyHuman* aim){
	*attacker -= aim;
}
