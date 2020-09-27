#include "CellStack.hpp"

	CellStack::CellStack(int size){
        m_data = new MyCell[size];
        m_length = 0;
    }
        
    void CellStack::Push(MyCell cell){//добавления клетки в стек            
		m_data[m_length] = cell;
        m_length++;
    }
    
    MyCell CellStack::Top(){//получение верхего элемента стека
    	return m_data[m_length-1];
    }
    
    int CellStack::getLength(){//получение количества элементов в стеке
        return this->m_length;
    }
           
    void CellStack::Remove(){//удаление верхнего элемента
        m_length--;
    }
    
    CellStack::~CellStack(){//деструктор; очищает выделенную память
        delete[] m_data;
    }
