#include "ControlPlayer.hpp"

ControlPlayer::ControlPlayer(int x, int y, MyMaze& maze){
	m_hero = new MyPlayer(x, y);
	m_position = maze.getCell(x,y);
}

void ControlPlayer::setPosition(MyMaze &maze){
	int x = 0;
	int y = 0;
	m_hero->getCoord(x, y);
	m_position = maze.getCell(x, y);
};

ControlPlayer& ControlPlayer::operator +=(MyMaze& maze){
	setPosition(maze);
	if (!m_position)
		return *this;
	m_position->getActObj()->Action(m_hero);
	m_position->setData(1, STATE_GROUND);
	m_position->setActObj(nullptr);
	return *this;
};

ControlPlayer:: ~ControlPlayer(){
	delete m_hero;
}

void ControlPlayer::showStats(){
	cout << m_hero->getHealth() << "\n";
}

int ControlPlayer::Move(MyMaze& maze, int dx, int dy){
	int x = 0;
	int y = 0;
	m_hero->getCoord(x, y);
	if (maze.getCell(x+dx, y+dy)->getPassable()){
		m_hero->Move(dx, dy);
		m_hero->getCoord(x, y);
		*this += maze;
		if (m_hero->getExit())
			cout << "Level completed!\n";
			return 2;
		return 1;
	}
	return 0;
}
