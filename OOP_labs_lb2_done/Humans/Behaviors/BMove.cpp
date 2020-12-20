#include "BMove.hpp"

void BMove::Action(MyHuman* first, MyHuman* second, int dx, int dy){
	first->Move(dx, dy);
}
