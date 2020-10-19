all: maze

maze: MyCell.o CellStack.o MyMaze.o MyInterface.o main.o MyHuman.o MyPlayer.o MyObject.o MyDynamite.o MyBonus.o MyAim.o
	g++ MyCell.o CellStack.o MyMaze.o MyInterface.o main.o MyHuman.o MyPlayer.o MyObject.o MyDynamite.o MyBonus.o MyAim.o -o maze
	
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
	
clean:
	rm -rf *.o maze
