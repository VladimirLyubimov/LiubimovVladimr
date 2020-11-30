#include "MyInterface.hpp"
MyInterface::MyInterface(){
	m_matrix = nullptr;
}

void MyInterface::getStartOfGenerationCoordinates(int &x, int &y){//получает координаты точки старта генерации с консоли
	cout << "Введите координаты точки старта генерации в формате x<пробел>y:\n";
	cin >> x >> y;
}
		
void MyInterface::getMazeSize(int &x, int &y){//получение линейных размеров лабиринта
	cout << "Введите линейнные размеры лабиринтав формате x<пробел>y:\n";
	cin >> x >> y;
}
    
void MyInterface::getStartAndFinish(int &xs, int &ys, int &xf, int &yf){//получает точки старта и финиша
    cout << "Сейчас вам будет предложено ввести координаты точек старта и финиша в формате x<пробел>y. Если\n";
    cout << "Введите координаты точки старта:\n";
	cin >> xs >> ys;
            
    cout << "Введите координаты точки финиша:\n";
	cin >> xf >> yf;
}

void MyInterface::getMove(int &dx, int &dy){
	char ch;
	cin >> ch;
	if (ch == 'w'){
		dy = -1;
		return;
	}
	if (ch == 's'){
		dy = 1;
		return;
	}
	if (ch == 'a'){
		dx = -1;
		return;
	}
	if (ch == 'd'){
		dx = 1;
		return;
	}
}
        
void MyInterface::printMaze(MyMaze &maze, MyPlayer* player){
	int i ,j, px, py;
	int x = maze.getWidth();
	int y = maze.getHeight();
	m_matrix = new char*[y];
	for(i = 0; i < y; i++)
		m_matrix[i] = new char[x];
	maze.getPrintMatrix(m_matrix);
		
	player->getCoord(px, py);
	m_matrix[py][px] = '!';
	
	for(i = 0; i < y; i++){
		j = 0;
		for(j; j < x; j++)
			cout << m_matrix[i][j];
		cout << "\n";
	}
	
	for(i = 0; i < y; i++)
		delete[] m_matrix[i];
	delete[] m_matrix; 
}
