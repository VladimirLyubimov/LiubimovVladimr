all: maze

maze: MyCell.o CellStack.o MyMaze.o MyInterface.o main.o
	g++ MyCell.o CellStack.o MyMaze.o MyInterface.o main.o -o maze
	
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
	
clean:
	rm -rf *.o maze
