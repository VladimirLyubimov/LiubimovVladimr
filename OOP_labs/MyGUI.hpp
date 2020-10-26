#pragma once
#include "SFML/Graphics.hpp"
#include "MyMaze.hpp"

using namespace sf;

class MyGUI{
	private:
		RenderWindow window;
		View MyView;
	private:
		void DrawMaze(MyMaze &maze);
	public:
		MyGUI(int x, int y);
		void Execute(MyMaze &maze);
}; 
