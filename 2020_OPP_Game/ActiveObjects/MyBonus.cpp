#include "MyBonus.hpp"

MyBonus::MyBonus(int x, int y): MyObject(x, y){
	m_type = STATE_BONUS;
};

void MyBonus::Action(MyPlayer* player, MyCell &cell){
	player->addExp(50);
	cell.setData(1, STATE_GROUND);
};
