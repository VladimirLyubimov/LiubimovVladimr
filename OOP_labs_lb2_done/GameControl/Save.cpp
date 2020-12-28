#include "Save.hpp"

Save::Save(const char* filename){
	m_file = new ofstream(filename, fstream::trunc | fstream::out);
	m_fname = new std::string(filename);
}

Save::~Save(){
	if(m_file->is_open()){
		m_file->close();
	}	
	delete m_file;
	delete m_fname;
}

const char* Save::getFilename(){
	return m_fname->data();
}

int Save::makeSave(PlayGround& field){
	if(!m_file->is_open())
		return 1;
		
	//write maze
	if(!field.m_maze)
		return 1;
	char** matrix;
	int x = field.m_maze->getWidth();
	int y = field.m_maze->getHeight();
	matrix = new char*[y];
	for(int i = 0; i < y; i++)
		matrix[i] = new char[x];
	field.m_maze->getPrintMatrix(matrix);
	
	*m_file << x << " " << y << "\n";
	for(int i = 0; i < y; i++){
		for(int j = 0; j < x; j++)
			*m_file << matrix[i][j];
		*m_file << "\n";
	}
	
	for(int i = 0; i < y; i++)
		delete[] matrix[i];
	delete[] matrix;
	
	//write player
	if(!field.m_hero)
		return 1;
	MyPlayer* hero = field.m_hero->getPlayer();
	hero->getCoord(x, y);
	*m_file << x << " " << y << " " << hero->getHealth() << " " << hero->getDamage() << " "<< hero->getLevel() << " " << hero->getExp() << " " << hero->getCoollected() << "\n";
	
	//write enemies
	if(!field.m_enemies)
		return 1;
	for(int i = 0; i < field.enemy_amount; i++){
		if(field.m_enemies[i]->getAlive()){
			field.m_enemies[i]->getCoord(x, y);
			*m_file << i << " " << x << " " << y << " " << field.m_enemies[i]->getHealth() << " " << field.m_enemies[i]->getDamage() << " " << field.m_enemies[i]->getLevel() << "\n";
		}
	}
	m_file->close();
	
	return 0;
}
