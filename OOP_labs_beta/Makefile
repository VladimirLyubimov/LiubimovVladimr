all: maze

maze: MyCell.o CellStack.o MyMaze.o MyInterface.o PlayerControl.o main.o MyHuman.o MyPlayer.o MyObject.o MyDynamite.o MyBonus.o MyAim.o MyGUI.o MyExit.o
	g++ MyCell.o CellStack.o MyMaze.o MyInterface.o PlayerControl.o main.o MyHuman.o MyPlayer.o MyObject.o MyDynamite.o MyBonus.o MyAim.o MyGUI.o MyExit.o -o maze -lsfml-graphics -lsfml-window -lsfml-system
	
main.o: main.cpp
	g++ -c main.cpp

MyCell.o: MyCell.cpp
	g++ -c MyCell.cpp
	
CellStack.o: CellStack.cpp
	g++ -c CellStack.cpp
	
MyMaze.o: MyMaze.cpp
	g++ -c MyMaze.cpp

MyInterface.o: MyInterface.cpp
	g++ -c MyInterface.cpp

PlayerControl.o: PlayerControl.cpp
	g++ -c PlayerControl.cpp

MyHuman.o:	MyHuman.cpp
	g++ -c MyHuman.cpp
	
MyPlayer.o: MyPlayer.cpp
	g++ -c MyPlayer.cpp
	
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

MyGUI: MyGUI.cpp
	g++ -c MyGUI.cpp -lsfml-graphics -lsfml-window -lsfml-system
	
clean:
	rm -rf *.o maze
