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
	char ch;
	SaveLoad sv;
			
	FileLog* Logfile = new FileLog("LogFile.txt");
	ConsolLog* consol = new ConsolLog();
	LogInterface* FLog = new LogInterface(Logfile);
	LogInterface* CLog = new LogInterface(consol);
	
	MyInterface interface;
	field.m_hero->MakeLog(FLog, CLog, field.m_hero->getPlayer());
	for(int i = 0; i< field.enemy_amount; i++){
		if(field.m_enemies[i])
			field.m_enemies[i]->MakeLog(FLog, CLog, field.m_enemies[i]);
	}
	
	interface.printMaze(*(field.m_maze), field.m_hero->getPlayer(), field.m_enemies, field.enemy_amount);

    while(1){
    	switch(interface.getGameCommand(dx, dy)){
    		case 1:
    			MyClear(Logfile, consol, FLog, CLog);
    			cout << "Start a new game! Do yo want to save it?(y/n)\n";
    			cin >> ch;
    			switch(ch){
					case 'y':
						sv.makeSave(field);
						break;
					default:
						break;
				}
    			return true;
    		case 2:
    			MyClear(Logfile, consol, FLog, CLog);
    			cout << "End game by player command! Do yo want to save it?(y/n)\n";
    			cin >> ch;
    			switch(ch){
					case 'y':
						sv.makeSave(field);
						break;
					default:
						break;
				}
    			return false;
    		case 0:
				if (field.m_hero->Move(*(field.m_maze), dx, dy, FLog, CLog) == 2){
					interface.printMaze(*(field.m_maze), field.m_hero->getPlayer(), field.m_enemies, field.enemy_amount);
					MyClear(Logfile, consol, FLog, CLog);
					return false;
				}
				for(int i = 0; i< field.enemy_amount; i++){
					if(field.m_enemies[i]){
						field.m_enemies[i]->makeTurn(*(field.m_maze));
						field.m_enemies[i]->MakeLog(FLog, CLog, field.m_enemies[i]);
					}
				}
				dx = 0;
				dy = 0;
				interface.printMaze(*(field.m_maze), field.m_hero->getPlayer(), field.m_enemies, field.enemy_amount);
				break;
    	}
    }
    return false;
}
