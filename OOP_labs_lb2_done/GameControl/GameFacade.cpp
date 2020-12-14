#include "GameFacade.hpp"

void GameFacade::Execute(){
	PlayGround field;
	
	GameInit::InitGame(field);
	while (GameExecutor::Play(field)){
		GameInit::EndGame(field);
		GameInit::InitGame(field);
	}
	GameInit::EndGame(field);
}
