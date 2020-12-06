#include "GameControl.hpp"

GameControl::GameControl(){
	int x_gs, y_gs, x_ms, y_ms, xs, ys, xf, yf;
	
	ifstream fin("TestData.txt");
	fin >> x_ms >> y_ms >> x_gs >> y_gs >> xs >> ys >> xf >> yf;

	m_finish = new MyExit();
	m_bonus = new MyBonus(); 
	m_aim = new MyAim();
	m_dynamite = new MyDynamite();
	
	m_maze = MyMaze::getInstance(x_ms,y_ms);
    m_maze->prepareForMaze(x_gs, y_gs, xs, ys, xf, yf, m_finish);
    m_maze->SetObjects(m_dynamite, m_aim, m_bonus);
	
	m_hero = new PlayerControl(ys, ys, *m_maze);
	
	fin.close();
}

GameControl::~GameControl(){
	delete m_finish;
	delete m_aim;
	delete m_bonus;
	delete m_dynamite;
	delete m_hero;
}

void GameControl::Execute(){
	int dx = 0;
	int dy = 0;
	
	FileLog* file = new FileLog("ObjectLog.txt");
	ConsolLog* consol = new ConsolLog();
	LogInterface Log(file, consol);
	
	m_interface.printMaze(*m_maze, m_hero->getPlayer());
    while(1){
    	m_interface.getMove(dx, dy);
    	if (m_hero->Move(*m_maze, dx, dy, Log) == 2){
    		cout << "The end!\n";
    		break;
    	}
    	dx = 0;
    	dy = 0;
    	m_interface.printMaze(*m_maze, m_hero->getPlayer());
    }
    m_interface.printMaze(*m_maze, m_hero->getPlayer());
    
    delete file;
    delete consol;
}
