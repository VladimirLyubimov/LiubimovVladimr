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
	
	//check content	
	for(int i = 0; i < y; i++){
		for(int j = 0; j < x; j++){
			switch(matrix[i][j]){
				case '@':
					break;
				case '1':
					break;
				case 'S':
					break;
				case 'A':
					break;
				case 'D':
					break;
				case 'B':
					break;	
				case 'F':
					break;
				default:
					return false;	
			}
		}
	}
	
	return true;
}

bool Load::checkPlayer(int x, int y, int health, int damage, int lev, int exp, int collect){
	//check coord
	if(x < 1 || y < 1)
		return false;
		
	//check stats
	if(health <= 0 || damage <= 0 || lev <= 0 || exp < 0 || collect < 0 || collect > 1)
		return false;
	
	return true;
}

bool Load::checkEnemy(int num, int x, int y, int health, int damage, int lev){
	//check coord
	if(x < 1 || y < 1)
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
		return 1;

	int height, width;
	char* c_st = new char[st.size() + 1];
	strcpy(c_st, st.data());
	char* pch;
	pch = strtok(c_st, " ");
	width = atoi(pch);
	pch = strtok(NULL, " ");
	height = atoi(pch);
	if(width % 2 != 1 || height % 2 != 1)
		return 1;
	
	//read maze grid
	char** matrix;
	matrix = new char*[height];
	for(int i = 0; i < height; i++)
		matrix[i] = new char[width];
	
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++)
			*m_file >> matrix[i][j];
	}
	
	if(!checkMatrix(matrix, width, height))
		return 1;
	
	field.m_maze = MyMaze::getInstance(width, height);
	field.m_finish = new MyExit();
	field.m_bonus = new MyBonus(); 
	field.m_aim = new MyAim();
	field.m_dynamite = new MyDynamite();
	field.m_maze->BuildFromMatrix(matrix, width, height, field.m_dynamite, field.m_aim, field.m_bonus, field.m_finish);
	if(!field.m_maze->startCheck())
		return 1;
	
	for(int i = 0; i < height; i++)
		delete[] matrix[i];
	delete[] matrix;
		
	//read player
	int x, y, health, damage, lev, exp, collect;
	*m_file >> x >> y >> health >> damage >> lev >> exp >> collect;
	
	if(!checkPlayer(x, y, health, damage, lev, exp, collect))
		return 1;
		
	//read enemies
	int num;
	while(1){
		*m_file >> num >> x >> y >> health >> damage >> lev;
		if(!checkEnemy(num, x, y, health, damage, lev))
			return 1;
		if(m_file->eof())
			break;
	}*/
	return 0;
}
