#include "BWait.hpp"

void BWait::Action(MyHuman* first, MyHuman* second, int dx, int dy){
	srand(time(NULL));
	second->takeDamage(1 + rand() % 20);
}
