#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "CellStack.hpp"
#include "MyCell.hpp"
#include "../ActiveObjects/MyObject.hpp"


class MyMaze{//класс игрового поля-лабиринта
    private:
    	static MyMaze* m_maze;
        MyCell** m_grid;
        int m_width;
        int m_height;
        
    private:
    	MyMaze(int set_x, int set_y);//Создаём заготовку под лабиринт. Все клетки, у которых обе координаты нечётны объявляются проходимыми, остальнные стенами.
    	MyMaze(const MyMaze &maze);//конструктор копирования
    	MyMaze(MyMaze &&maze);//конструктор перемещения
    	MyMaze& operator= (MyMaze &&maze);//оператор присваивания перемещением
    	MyMaze& operator= (const MyMaze &maze);//оператор присваивания копированием
    	int checkNeighbours(int x, int y, int* &cells);//получает координаты клетки и массив для записи возможных направлений из этой клетки. проверяет соседей клетки на поссещённость. Если они непосещены, записывает их направление в массив и увеличивет счётчик направлений на 1. Возвращает количество непосещённых соседей клетки. Соседями называются клетки с индексом отличным только по вертикали или горизонтали от индекса входной клетки на 2.
    	void setStartFinish(int xs, int ys, int xf, int yf, MyObject* finish);//устанавливает точеи старта и финиша
    	void makeMaze(CellStack &stack);//Рекурсивная функция генерации лабиринта. Схожа с обходом в глубину в графе. Полчает на вход стек с клетками, если он пуст завершает выполнение (припервом вызове стек не пуст). Проверяет верхний элемент стека на наличие непосещённых соседей. Если их нет удаляет верхний элемент стека и вызывает себя от изменённого стека. Если есть - выбирает случайного соседа, соеденяет текущую клетку с эти соседом, добавляет соседа в стек и вызывает себя от изменённого стека.
    	
    public:
    	static MyMaze* getInstance(int x, int y);//метод для реализации паттерна синглтон   	
    	void prepareForMaze(int x, int y, int xs, int ys, int xf, int yf, MyObject* finish);//получает координаты стартовой клетки помещает её в стек, отмечая её помеченной и запускает рекурсивную функцию генерации лабиринта.
    	void getPrintMatrix(char** &matrix);//возвращает массив символов для вывода лабиринта
    	int getWidth();
    	int getHeight();
    	void SetObjects(MyObject* bomb, MyObject* aim, MyObject* bonus);
    	MyCell* getCell(int x, int y);
    	static void Clear();
    	~MyMaze();
};
