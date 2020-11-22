#pragma once
#include "SFML/Graphics.hpp"
#include "MyMaze.hpp"
#include "iostream"

using namespace sf;

class MyGUI{
	private:
		RenderWindow window;
		View MyView;
	private:
		void DrawMaze(MyMaze &maze);
		void ViewControl();
	public:
		MyGUI(int x, int y);
		void Execute(MyMaze &maze);
		Sprite* getSprite(const char* filename);
}; 
