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
    
    field.enemy_amount = 6;
    field.m_enemies = new SuperEnemy*[field.enemy_amount];
    for(int i = 0; i < field.enemy_amount; i += 3){
    	field.m_enemies[i] = new Enemy<BAttack>(i*2+1, field.m_maze->getHeight()/2 - 3, 800, 8, 1, *(field.m_maze));
    	field.m_enemies[i+1] = new Enemy<BDamage>((i+1)*2+1, field.m_maze->getHeight()/2 - 3, 800, 8, 1, *(field.m_maze));
    	field.m_enemies[i+2] = new Enemy<BLevel>((i+2)*2+1, field.m_maze->getHeight()/2 - 3, 800, 8, 1, *(field.m_maze));
    }
	
	fin.close();
}

void GameInit::EndGame(PlayGround& field){
	//Save s("Save.txt");
	//s.makeSave(field);
	Load l("Save.txt");
	l.makeLoad(field);
	delete field.m_finish;
	delete field.m_aim;
	delete field.m_bonus;
	delete field.m_dynamite;
	delete field.m_hero;
	field.m_maze->Clear();
	field.m_finish = nullptr;
	field.m_aim = nullptr;
	field.m_bonus = nullptr;
	field.m_dynamite = nullptr;
	field.m_hero = nullptr;
	
	for (int i = 0; i < field.enemy_amount; i++){
		delete field.m_enemies[i];
	}
	delete[] field.m_enemies;
	field.m_enemies = nullptr;
}
