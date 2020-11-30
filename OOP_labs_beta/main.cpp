//Mady by Vladimir Lyubimov, ETU 2020.
#include "MyCell.hpp"
#include "CellStack.hpp"
#include "MyMaze.hpp"
#include "MyInterface.hpp"
#include "MyPlayer.hpp"
#include "MyGUI.hpp"
#include "PlayerControl.hpp"
#include "./ActiveObjects/MyDynamite.hpp"
#include "./ActiveObjects/MyExit.hpp"
#include "./ActiveObjects/MyBonus.hpp"
#include "./ActiveObjects/MyAim.hpp"

using namespace std;

int main(){
	int x_gs, y_gs, x_ms, y_ms, xs, ys, xf, yf;
	int dx = 0;
	int dy = 0;
	MyInterface interface;
	//hero.levelup();
	//hero.changeLevel(0);
	//cout << hero.CalcDamage(1,0, 1000) << "\n";

	interface.getMazeSize(x_ms, y_ms);
	interface.getStartOfGenerationCoordinates(x_gs, y_gs);
    interface.getStartAndFinish(xs, ys, xf, yf);

	//MyGUI gui(x_ms*50, y_ms*50);

	MyExit* finish = new MyExit();
	MyBonus* bonus = new MyBonus(); 
	MyAim* aim = new MyAim();
	MyDynamite* dynamite = new MyDynamite();
		
	MyMaze &maze = MyMaze::getInstance(x_ms,y_ms);
    maze.prepareForMaze(x_gs, y_gs, xs, ys, xf, yf, finish);
    maze.SetObjects(dynamite, aim, bonus); 
    PlayerControl hero(ys, ys, maze);
   	interface.printMaze(maze, hero.getPlayer());
    while(1){
    	interface.getMove(dx, dy);
    	if (hero.Move(maze, dx, dy) == 2){
    		cout << "The end!\n";
    		break;
    	}
    	dx = 0;
    	dy = 0;
    	interface.printMaze(maze, hero.getPlayer());
    }
    //maze.getCell(1,1)->setActObj(&Dynamite);

    //hero.showStats();
    //hero.Move(maze, 0, 0);
    //hero.showStats();
    //gui.Execute(maze);
	//interface.printMaze(maze);
	return 0; 
}
