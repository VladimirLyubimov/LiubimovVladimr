#include "PlayerControl.hpp"

PlayerControl::PlayerControl(int x, int y, MyMaze& maze){
	m_hero = new MyPlayer(x, y);
	m_position = maze.getCell(x,y);
}

void PlayerControl::setPosition(MyMaze &maze){
	int x = 0;
	int y = 0;
	m_hero->getCoord(x, y);
	m_position = maze.getCell(x, y);
};

PlayerControl:: ~PlayerControl(){
	delete m_hero;
}

void PlayerControl::showStats(){
	cout << "Health = " << m_hero->getHealth() << "\n";
	cout << "Level = " << m_hero->getLevel() << "\n";
	cout << "Experience = " << m_hero->getExp() << "\n";
}

MyPlayer* PlayerControl::getPlayer(){
	return m_hero;
}

int PlayerControl::Move(MyMaze& maze, int dx, int dy){
	int x = 0;
	int y = 0;
	bool success = false;
	m_hero->getCoord(x, y);
	if (maze.getCell(x+dx, y+dy)->getPassable()){
		m_hero->Move(dx, dy);
		m_hero->getCoord(x, y);
		cout << x << " " << y << "\n";
		m_position = maze.getCell(x, y);
		if (m_position->getActObj()){
			if(*(m_position->getActObj()) += m_hero){
				cout << "interacted\n";
				m_position->setData(1, STATE_GROUND);
				m_position->setActObj(nullptr);
			}
		}
		if (m_hero->getExit()){
			cout << "Level completed!\n";
			return 2;
		}
		showStats();
		return 1;
	}
	return 0;
}
