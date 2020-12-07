#include "GameExecutor.hpp"

void GameExecutor::Play(PlayGround& field){
	int dx = 0;
	int dy = 0;
	
	FileLog* Logfile = new FileLog("LogFile.txt");
	ConsolLog* consol = new ConsolLog();
	LogInterface* FLog = new LogInterface(Logfile);
	LogInterface* CLog = new LogInterface(consol);
	
	MyInterface interface;
	interface.printMaze(*(field.m_maze), field.m_hero->getPlayer());
	
    while(1){
    	interface.getMove(dx, dy);
    	if (field.m_hero->Move(*(field.m_maze), dx, dy, FLog, CLog) == 2){
    		break;
    	}
    	dx = 0;
    	dy = 0;
    	interface.printMaze(*(field.m_maze), field.m_hero->getPlayer());
    }
    interface.printMaze(*(field.m_maze), field.m_hero->getPlayer());
    
    delete Logfile;
    delete consol;
    delete FLog;
    delete CLog;
}
