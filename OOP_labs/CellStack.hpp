#pragma once
#include <cstdlib>
#include "MyCell.hpp"

class CellStack{//стек клеток; необходим для генерации лабиринта; реализованы только необходимые методы
    private:
        MyCell* m_data;
        int m_length;
    public:
    	CellStack(int size);
    	void Push(MyCell cell);//добавления клетки в стек
    	MyCell Top();//получение верхего элемента стека
    	int getLength();//получение количества элементов в стеке
    	void Remove();//удаление верхнего элемента
    	~CellStack();//деструктор; очищает выделенную память
};
