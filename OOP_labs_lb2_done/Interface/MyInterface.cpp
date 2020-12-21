#include "MyInterface.hpp"
MyInterface::MyInterface(){
	m_matrix = nullptr;
}

int MyInterface::getGameCommand(int &dx, int &dy){
	char ch;
	cin >> ch;
	switch(ch){
		case 'n':
			return 1;
		case 'e':
			return 2;
		case 'w':
			dy = -1;
			return 0;
		case 's':
			dy = 1;
			return 0;
		case 'a':
			dx = -1;
			return 0;
		case 'd':
			dx = 1;
			return 0;
	}
	return 0;
}
        
void MyInterface::printMaze(MyMaze &maze, MyPlayer* player, SuperEnemy** enemies, int len){
	int i ,j, px, py;
	int x = maze.getWidth();
	int y = maze.getHeight();
	m_matrix = new char*[y];
	for(i = 0; i < y; i++)
		m_matrix[i] = new char[x];
	maze.getPrintMatrix(m_matrix);
		
	player->getCoord(px, py);
	m_matrix[py][px] = '!';
	
	for(i = 0; i < len; i++){
		if(enemies[i]->getAlive()){
			enemies[i]->getCoord(px, py);
			m_matrix[py][px] = 'E';
		}
	}
	
	for(i = 0; i < y; i++){
		j = 0;
		for(j; j < x; j++)
			if(m_matrix[i][j] == '1'){
				cout << ' ';
			}else
				cout << m_matrix[i][j];
		cout << "\n";
	}
	
	for(i = 0; i < y; i++)
		delete[] m_matrix[i];
	delete[] m_matrix; 
}
