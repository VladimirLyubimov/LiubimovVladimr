#include "Load.hpp"

Load::Load(const char* filename){
	m_file = new ifstream(filename, fstream::in);
}

Load::~Load(){
	if(m_file->is_open())
		m_file->close();
	delete m_file;
}

bool Load::checkData(string& data, const char* pattern){
	regex_t rexp;
	regmatch_t pm;
	regcomp(&rexp, pattern, REG_EXTENDED);
	if(!regexec(&rexp, data.data(), 0, &pm, 0)){
		regfree(&rexp);
		return true;
	}
	
	regfree(&rexp);
	return false;	
}

bool Load::checkMatrix(char** matrix, int x, int y){
	//check out walls
	for(int i = 0; i < x; i++){
		if(matrix[0][i] != '@' || matrix[y-1][i] != '@')
			return false;
	}
	
	for(int i = 0; i < y; i++){
		if(matrix[i][0] != '@' || matrix[i][x-1] != '@')
			return false;
	}
	return true;
}

bool Load::checkPlayer(int x, int y, int health, int damage, int lev, int width, int height){
	//check coord
	if(x < 1 || y < 1 || x >= width - 1 || y >= height - 1)
		return false;
		
	//check stats
	if(health <= 0 || damage <= 0 || lev <= 0)
		return false;
	
	return true;
}

bool Load::checkEnemy(int num, int x, int y, int health, int damage, int lev, int width, int height){
	//check coord
	if(x < 1 || y < 1 || x >= width - 1 || y >= height - 1)
		return false;
	
	//check stats	
	if(health <= 0 || damage <= 0 || lev <= 0 || num < 0)
		return false;
	
	return true;
}

int Load::makeLoad(PlayGround& field){
	if(!m_file->is_open())
		return 1;
	
	string st;
	
	//read maze
	//read maze size
	getline(*m_file, st);
	if(!checkData(st, "^[0-9]+\\s[0-9]+$"))
		return 2;

	int height, width;
	char* c_st = new char[st.size() + 1];
	strcpy(c_st, st.data());
	char* pch;
	pch = strtok(c_st, " ");
	width = atoi(pch);
	pch = strtok(NULL, " ");
	height = atoi(pch);
	delete[] c_st;
	if(width % 2 != 1 || height % 2 != 1)
		return 2;
	
	//read maze grid
	char** matrix;
	matrix = new char*[height];
	for(int i = 0; i < height; i++)
		matrix[i] = new char[width];
	
	for(int i = 0; i < height; i++){
		getline(*m_file, st);
		if(!checkData(st, "^@[1@SFDBA]+@$") || st.size() != width){
			return 2;
		}
		for(int j = 0; j < width; j++){
			matrix[i][j] = st[j];
		}
	}
	
	if(!checkMatrix(matrix, width, height))
		return 2;
	
	field.m_maze = MyMaze::getInstance(width, height);
	field.m_finish = new MyExit();
	field.m_bonus = new MyBonus(); 
	field.m_aim = new MyAim();
	field.m_dynamite = new MyDynamite();
	field.m_maze->BuildFromMatrix(matrix, width, height, field.m_dynamite, field.m_aim, field.m_bonus, field.m_finish);
	if(!field.m_maze->startCheck())
		return 2;
	
	for(int i = 0; i < height; i++)
		delete[] matrix[i];
	delete[] matrix;
		
	//read player
	int x, y, health, damage, lev, exp;
	bool collect = false;
	getline(*m_file, st);
	if(!checkData(st, "^[0-9]+\\s[0-9]+\\s[0-9]+\\s[0-9]+\\s[0-9]+\\s[0-9]+\\s[01]$")){
		return 3;
	}
	c_st = new char[st.size() + 1];
	strcpy(c_st, st.data());
	x = atoi(strtok(c_st, " "));
	y = atoi(strtok(NULL, " "));
	health = atoi(strtok(NULL, " "));
	damage = atoi(strtok(NULL, " "));
	lev = atoi(strtok(NULL, " "));
	exp = atoi(strtok(NULL, " "));
	if(atoi(strtok(NULL, " "))){
		collect = true;
	}
	delete[] c_st;	
	
	if(!checkPlayer(x, y, health, damage, lev, width, height))
		return 3;
			
	field.m_hero = new PlayerControl(x, y, *(field.m_maze), health, damage, lev, collect);
	if(collect)
		field.m_hero->getPlayer()->setCollected();
	
	//read enemies
	int num;
	int i = 0;
	field.enemy_amount = 3*(field.m_maze->getWidth()/2)/3;
    field.m_enemies = new SuperEnemy*[field.enemy_amount];
    for(i; i < field.enemy_amount; i++)
		field.m_enemies[i] = nullptr;
	i = 0;
	while(1){
		if(!getline(*m_file, st)){
			break;
		}
		if(!checkData(st, "^[0-9]+\\s[0-9]+\\s[0-9]+\\s[0-9]+\\s[0-9]+\\s[0-9]+$")){
			return 4;
		}
		c_st = new char[st.size() + 1];
		strcpy(c_st, st.data());
		num = atoi(strtok(c_st, " "));
		x = atoi(strtok(NULL, " "));
		y = atoi(strtok(NULL, " "));
		health = atoi(strtok(NULL, " "));
		damage = atoi(strtok(NULL, " "));
		lev = atoi(strtok(NULL, " "));
		delete[] c_st;
		if(!checkEnemy(num, x, y, health, damage, lev, width, height)){
			return 4;
		}
		if(num > field.enemy_amount)
			return 4;
		switch (num % 3){
			case 0:
				field.m_enemies[i] = new Enemy<BAttack>(x, y, health, damage, lev, *(field.m_maze));
				i += 1;
				break;
			case 1:
				field.m_enemies[i] = new Enemy<BDamage>(x, y, health, damage, lev, *(field.m_maze));
				i += 1;
				break;
			case 2:
				field.m_enemies[i] = new Enemy<BLevel>(x, y, health, damage, lev, *(field.m_maze));
				i += 1;
				break;
		}
	}
	
	return 0;
}
