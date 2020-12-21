#include "Load.hpp"

Load::Load(const char* filename){
	m_file = new ifstream(filename, fstream::in);
}

Load::~Load(){
	if(m_file->is_open())
		m_file->close();
	delete m_file;
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

bool Load::checkPlayer(int x, int y, int health, int damage, int lev, int exp, int collect, int width, int height)

int Load::makeLoad(PlayGround& field){
	if(!m_file->is_open())
		return 1;
		
	//read maze
	int height, width;
	*m_file >> width >> height;
	
	if(width % 2 != 1 || height % 2 != 1)
		return 1;
	
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
		
	//read player
	int x, y, health, damage, lev, exp, collect;
	*m_file >> x >> y >> health >> damage >> lev >> exp >> collect;
	cout << x << y << health << damage << lev << exp << collect;
}
