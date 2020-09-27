#include "MyInterface.hpp"

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
        
void MyInterface::printMaze(MyMaze maze){
	maze.print();
}
