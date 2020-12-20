#include "EnemyControl.hpp"

EnemyControl::EnemyControl(int x, int y, MyMaze& maze){
	m_beh = new BMove();
	m_enemy = new Enemy<Behavior>(x, y, 800, 8, 1, m_beh);
	m_position = maze.getCell(x,y);
	m_position->setIsHuman(m_enemy);
}

EnemyControl::~EnemyControl(){
	delete m_enemy;
	delete m_beh;
}

Enemy<Behavior>* EnemyControl::getPlayer(){
	return m_enemy;
}

void EnemyControl::setPosition(MyMaze &maze){
	int x = 0;
	int y = 0;
	m_enemy->getCoord(x, y);
	m_position = maze.getCell(x, y);
}

MyHuman* EnemyControl::checkSurround(MyHuman* aim, MyMaze& maze){
	int x = 0;
	int y = 0;
	m_enemy->getCoord(x, y);
	aim = maze.getCell(x+1,y)->getIsHuman();
	if(aim)
		return aim;
		
	aim = maze.getCell(x,y+1)->getIsHuman();
	if(aim)
		return aim;
		
	aim = maze.getCell(x-1,y)->getIsHuman();
	if(aim)
		return aim;
		
	aim = maze.getCell(x,y-1)->getIsHuman();
	if(aim)
		return aim;
	
	return nullptr;
}

void EnemyControl::makeTurn(MyMaze& maze){
	Behavior* abeh = new BAttack();
	Behavior* mbeh = new BMove();
	Behavior* wbeh = new BWait();
	
	MyHuman* aim = nullptr;
	aim = checkSurround(aim, maze);
	if(aim){
		m_enemy->setBehavior(abeh);
		m_enemy->makeTurn(aim, 0, 0);
		return;
	}
	
	srand(time(NULL));
	int a = rand() % 2;
	
	int x = 0;
	int y = 0;
	m_enemy->getCoord(x, y);
	maze.getCell(x,y)->setIsHuman(nullptr);
	cout << "a\n";
	//m_enemy->makeTurn(aim, -1, 0);
	m_enemy->Move(-1,0);
	maze.getCell(x-1,y)->setIsHuman(m_enemy);
	return;
	
	/*switch(a){
		case 0:
			m_enemy->setBehavior(wbeh);
			m_enemy->makeTurn(aim, 0, 0);
			return;
		case 1:
			m_enemy->setBehavior(mbeh);
			srand(time(NULL));
			int way = rand() % 4;
			int x = 0;
			int y = 0;
			m_enemy->getCoord(x, y);
			
			switch(way){
				case 0:
					if(maze.getCell(x+1,y)->getPassable()){
						maze.getCell(x,y)->setIsHuman(nullptr);
						//cout << "d\n";
						m_enemy->makeTurn(aim, 1, 0);
						maze.getCell(x+1,y)->setIsHuman(m_enemy);
						return;
					}
				
				case 1:
					if(maze.getCell(x,y+1)->getPassable()){
						maze.getCell(x,y)->setIsHuman(nullptr);
						//cout << "s\n";
						m_enemy->makeTurn(aim, 0, 1);
						maze.getCell(x,y+1)->setIsHuman(m_enemy);
						return;
					}
					
				case 2:
					if(maze.getCell(x-1,y)->getPassable()){
						maze.getCell(x,y)->setIsHuman(nullptr);
						//cout << "a\n";
						m_enemy->makeTurn(aim, -1, 0);
						maze.getCell(x-1,y)->setIsHuman(m_enemy);
						return;
					}
				
				case 3:
					if(maze.getCell(x,y-1)->getPassable()){
						maze.getCell(x,y)->setIsHuman(nullptr);
						//cout << "w\n";
						m_enemy->makeTurn(aim, 0, -1);
						maze.getCell(x,y-1)->setIsHuman(m_enemy);
						return;
					}

			}
			
			cout << "nope\n";
			m_enemy->setBehavior(wbeh);
			m_enemy->makeTurn(aim, 0, 0);
			return;
	}*/
	
	delete abeh;
	delete mbeh;
	delete wbeh;
}
