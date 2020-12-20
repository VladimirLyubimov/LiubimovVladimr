#include "BWait.hpp"

void BWait::Action(MyHuman* first, MyHuman* second, int dx, int dy){
	srand(time(NULL));
	first->takeDamage(rand() % 10);
}
