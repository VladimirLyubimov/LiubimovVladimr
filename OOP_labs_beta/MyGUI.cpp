#include "MyGUI.hpp"

MyGUI::MyGUI(int x, int y){
	window.create(VideoMode(x, y), "Game in maze!");
	MyView.reset(FloatRect(0,0,50,50));
}

void MyGUI::Execute(MyMaze &maze){
	while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed){
                window.close();
            }
        }

		DrawMaze(maze);
        window.display();
        //ViewControl();
        //window.setView(MyView);
    }
}

void MyGUI::ViewControl(){
	if (Keyboard::isKeyPressed(Keyboard::W))
		MyView.move(0, -50);
	if (Keyboard::isKeyPressed(Keyboard::D))
		MyView.move(50, 0);
	if (Keyboard::isKeyPressed(Keyboard::S))
		MyView.move(0, 50);
	if (Keyboard::isKeyPressed(Keyboard::A))
		MyView.move(-50, 0);
}

Sprite* MyGUI::getSprite(const char* filename){
	Sprite* sprite = new Sprite[1];
	Texture* texture = new Texture[1];
	texture->loadFromFile(filename, IntRect(0, 0, 50, 50));
	sprite->setTexture(*texture);
	return sprite;
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
	
	static Sprite* brick = getSprite("./textures/brick.jpg");
	static Sprite* floor = getSprite("./textures/floor.jpg");
	
	for(i = 0; i < y; i++){
		j = 0;
		for(j; j < x; j++){
			if (matrix[i][j] == ' '){
				floor->setPosition(50*i, 50*j);
				window.draw(*floor);
				continue;
			}
			if (matrix[i][j] == '@'){
				brick->setPosition(50*i, 50*j);
				window.draw(*brick);
				continue;
			}
		}
	}
	
	for(i = 0; i < y; i++)
		delete[] matrix[i];
	delete[] matrix; 
}
