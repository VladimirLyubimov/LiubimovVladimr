#include "GameFacade.hpp"

void GameFacade::Execute(){
	PlayGround field;
	GameInit::InitGame(field);
	GameExecutor::Play(field);
	GameInit::EndGame(field);
}
