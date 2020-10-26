//Mady by Vladimir Lyubimov, ETU 2020.
#include "MyCell.hpp"
#include "CellStack.hpp"
#include "MyMaze.hpp"
#include "MyInterface.hpp"
#include "MyPlayer.hpp"
#include "MyGUI.hpp"

using namespace std;

int main()
{
	int x_gs, y_gs, x_ms, y_ms, xs, ys, xf, yf;
	MyInterface interface;
	//MyPlayer hero(1, 1);
	//hero.levelup();
	//hero.changeLevel(0);
	//cout << hero.CalcDamage(1,0, 1000) << "\n";

	interface.getMazeSize(x_ms, y_ms);
	interface.getStartOfGenerationCoordinates(x_gs, y_gs);
    interface.getStartAndFinish(xs, ys, xf, yf);

	MyGUI gui(x_ms*50, y_ms*50);

	MyMaze &maze = MyMaze::getInstance(x_ms,y_ms);
    maze.prepareForMaze(x_gs, y_gs, xs, ys, xf, yf);
    
    gui.Execute(maze);
	//interface.printMaze(maze);
	return 0; 
}
