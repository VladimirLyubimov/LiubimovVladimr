all: maze

maze: MyCell.o CellStack.o MyMaze.o MyInterface.o PlayerControl.o main.o GameControl.o MyHuman.o MyPlayer.o MyObject.o MyDynamite.o MyBonus.o MyAim.o MyExit.o
	g++ MyCell.o CellStack.o MyMaze.o MyInterface.o PlayerControl.o main.o GameControl.o MyHuman.o MyPlayer.o MyObject.o MyDynamite.o MyBonus.o MyAim.o MyExit.o -o maze -lsfml-graphics -lsfml-window -lsfml-system
	
main.o: main.cpp
	g++ -c main.cpp

MyCell.o: ./Maze/MyCell.cpp
	g++ -c ./Maze/MyCell.cpp
	
CellStack.o: ./Maze/CellStack.cpp
	g++ -c ./Maze/CellStack.cpp
	
MyMaze.o: ./Maze/MyMaze.cpp
	g++ -c ./Maze/MyMaze.cpp

MyInterface.o: ./Interface/MyInterface.cpp
	g++ -c ./Interface/MyInterface.cpp

PlayerControl.o: ./Humans/PlayerControl.cpp
	g++ -c ./Humans/PlayerControl.cpp

MyHuman.o:	./Humans/MyHuman.cpp
	g++ -c ./Humans/MyHuman.cpp
	
MyPlayer.o: ./Humans/MyPlayer.cpp
	g++ -c ./Humans/MyPlayer.cpp
	
MyObject.o: ./ActiveObjects/MyObject.cpp
	g++ -c ./ActiveObjects/MyObject.cpp
	
MyDynamite.o: ./ActiveObjects/MyDynamite.cpp
	g++ -c ./ActiveObjects/MyDynamite.cpp
	
MyBonus.o: ./ActiveObjects/MyBonus.cpp
	g++ -c ./ActiveObjects/MyBonus.cpp
	
MyAim.o: ./ActiveObjects/MyAim.cpp
	g++ -c ./ActiveObjects/MyAim.cpp	

MyExit.o: ./ActiveObjects/MyExit.cpp
	g++ -c ./ActiveObjects/MyExit.cpp
	
GameControl.o: GameControl.cpp
	g++ -c GameControl.cpp
	
clean:
	rm -rf *.o maze
