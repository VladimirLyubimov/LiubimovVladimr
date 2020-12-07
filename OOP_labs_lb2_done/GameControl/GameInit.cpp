#include "GameInit.hpp"

void GameInit::InitGame(PlayGround& field){
	int x_gs, y_gs, x_ms, y_ms, xs, ys, xf, yf;
	
	ifstream fin("TestData.txt");
	fin >> x_ms >> y_ms >> x_gs >> y_gs >> xs >> ys >> xf >> yf;

	field.m_finish = new MyExit();
	field.m_bonus = new MyBonus(); 
	field.m_aim = new MyAim();
	field.m_dynamite = new MyDynamite();
	
	field.m_maze = MyMaze::getInstance(x_ms,y_ms);
    field.m_maze->prepareForMaze(x_gs, y_gs, xs, ys, xf, yf, field.m_finish);
    field.m_maze->SetObjects(field.m_dynamite, field.m_aim, field.m_bonus);
    
    field.m_hero = new PlayerControl(ys, ys, *(field.m_maze));
	
	fin.close();
}

void GameInit::EndGame(PlayGround& field){
	delete field.m_finish;
	delete field.m_aim;
	delete field.m_bonus;
	delete field.m_dynamite;
	delete field.m_hero;
}
