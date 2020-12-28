#include "GameFacade.hpp"

void GameFacade::Execute(){
	PlayGround field;
	SaveLoad sv;
	
	char ch;
	cout << "Do you want to load game?(y/n)\n";
	cin >> ch;
	switch(ch){
		case 'y':
			sv.makeLoad(field);
			break;
		default:
			GameInit::InitGame(field);
			break;
	}

	while (GameExecutor::Play(field)){
		GameInit::EndGame(field);
		GameInit::InitGame(field);
	}
	GameInit::EndGame(field); 
}
