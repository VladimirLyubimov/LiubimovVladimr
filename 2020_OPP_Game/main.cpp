//Mady by Vladimir Lyubimov, ETU 2020.
#include "MyCell.hpp"
#include "CellStack.hpp"
#include "MyMaze.hpp"
#include "MyInterface.hpp"

using namespace std;

int main()
{
	int x_gs, y_gs, x_ms, y_ms, xs, ys, xf, yf;
	MyInterface interface;

	interface.getMazeSize(x_ms, y_ms);
	interface.getStartOfGenerationCoordinates(x_gs, y_gs);
    interface.getStartAndFinish(xs, ys, xf, yf);

	MyMaze maze(x_ms,y_ms);
    maze.prepareForMaze(x_gs, y_gs, xs, ys, xf, yf);

	interface.printMaze(maze);
}

