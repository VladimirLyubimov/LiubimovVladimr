#include "MyGUI.hpp"

MyGUI::MyGUI(int x, int y){
	window.create(VideoMode(x, y), "Game in maze!");
}

void MyGUI::Execute(MyMaze &maze){
	while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

		DrawMaze(maze);
        window.display();
    }
}

void MyGUI::DrawMaze(MyMaze &maze){
	char** matrix;
	int i ,j;
	int x = maze.getWidth();
	int y = maze.getHeight();
	matrix = new char*[y];
	for(i = 0; i < y; i++)
		matrix[i] = new char[x];
	maze.getPrintMatrix(matrix);
	
	Texture tbrick;
	Texture tfloor;
	tbrick.loadFromFile("./textures/brick.jpg", IntRect(0, 0, 50, 50));
	tfloor.loadFromFile("./textures/floor.jpg", IntRect(0, 0, 50, 50));
	Sprite brick(tbrick);
	Sprite floor(tfloor);
	
	for(i = 0; i < y; i++){
		j = 0;
		for(j; j < x; j++){
			if (matrix[i][j] == ' '){
				floor.setPosition(50*i, 50*j);
				window.draw(floor);
				continue;
			}
			if (matrix[i][j] == '@'){
				brick.setPosition(50*i, 50*j);
				window.draw(brick);
				continue;
			}
		}
	}
	
	for(i = 0; i < y; i++)
		delete[] matrix[i];
	delete[] matrix; 
}
