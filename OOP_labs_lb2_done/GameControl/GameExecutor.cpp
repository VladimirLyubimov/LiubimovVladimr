#include "GameExecutor.hpp"

void GameExecutor::MyClear(FileLog* Logfile, ConsolLog* consol, LogInterface* FLog, LogInterface* CLog){
	delete Logfile;
    delete consol;
    delete FLog;
    delete CLog;
}

bool GameExecutor::Play(PlayGround& field){
	int dx = 0;
	int dy = 0;
	
	FileLog* Logfile = new FileLog("LogFile.txt");
	ConsolLog* consol = new ConsolLog();
	LogInterface* FLog = new LogInterface(Logfile);
	LogInterface* CLog = new LogInterface(consol);
	
	MyInterface interface;
	field.m_hero->MakeLog(FLog, CLog, field.m_hero->getPlayer());
	interface.printMaze(*(field.m_maze), field.m_hero->getPlayer());
	
    while(1){
    	switch(interface.getGameCommand(dx, dy)){
    		case 1:
    			MyClear(Logfile, consol, FLog, CLog);
    			cout << "Start a new game!\n";
    			return true;
    		case 2:
    			MyClear(Logfile, consol, FLog, CLog);
    			cout << "End game by player command!\n";
    			return false;
    		case 0:
				if (field.m_hero->Move(*(field.m_maze), dx, dy, FLog, CLog) == 2){
					interface.printMaze(*(field.m_maze), field.m_hero->getPlayer());
					MyClear(Logfile, consol, FLog, CLog);
					return false;
				}
				dx = 0;
				dy = 0;
				interface.printMaze(*(field.m_maze), field.m_hero->getPlayer());
				break;
    	}
    }
    return false;
}
