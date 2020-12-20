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

MyPlayer* PlayerControl::getPlayer(){
	return m_hero;
}

template <class T>
void PlayerControl::MakeLog(LogInterface* FLog, LogInterface* CLog, T* LogObj){
	if(FLog)
		*FLog << LogObj;
	if(CLog)
		*CLog << LogObj;
}

int PlayerControl::Move(MyMaze& maze, int dx, int dy, LogInterface* FLog, LogInterface* CLog){
	int x = 0;
	int y = 0;
	
	m_hero->getCoord(x, y);
	if (maze.getCell(x+dx, y+dy)->getPassable()){
		m_position->setIsHuman(nullptr);
		m_hero->Move(dx, dy);
		m_hero->getCoord(x, y);
		m_position = maze.getCell(x, y);
		m_position->setIsHuman(m_hero);
		if (m_position->getActObj()){
			if(*(m_position->getActObj()) += m_hero){
				MakeLog(FLog, CLog, m_position->getActObj());
				m_position->setData(1, STATE_GROUND);
				m_position->setActObj(nullptr);
			}
		}
		MakeLog(FLog, CLog, m_hero);
		if (m_hero->getHealth() <= 0){
			m_position->setIsHuman(nullptr);
			return 2;
		}
		if (m_hero->getExit()){
			m_position->setIsHuman(nullptr);
			return 2;
		}
		return 1;
	}
	MakeLog(FLog, CLog, m_hero);
	return 0;
}
