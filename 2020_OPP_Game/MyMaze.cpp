#include "MyMaze.hpp"

	MyMaze::MyMaze(int set_x, int set_y){//Создаём заготовку под лабиринт. Все клетки, у которых обе координаты нечётны объявляются проходимыми, остальнные стенами.
        m_width = set_x;
        m_height = set_y;
        m_grid = new MyCell*[m_height];
        for (int i = 0; i < m_height; i++){
            m_grid[i] = new MyCell[m_width];
            for (int j = 0; j < m_width; j++){
                if ((i%2 == 1) && (j%2 == 1))
                    m_grid[i][j].setData(1, STATE_GROUND);
                m_grid[i][j].setCoordinates(j,i);
            }
        }
	}

	MyMaze::MyMaze(const MyMaze &maze){//конструктор копирования
		m_height = maze.m_height;
		m_width = maze.m_width;
		m_grid = new MyCell*[m_height];
		for (int i = 0; i < m_height; i++){
            m_grid[i] = new MyCell[m_width];
            for (int j = 0; j < m_width; j++)
				m_grid[i][j] = maze.m_grid[i][j];
		}
	}
    
    MyMaze::MyMaze(MyMaze &&maze){//конструктор перемещения
        m_height = maze.m_height;
		m_width = maze.m_width;
        m_grid = maze.m_grid;
            
        maze.m_grid = nullptr;
    }
    
    MyMaze& MyMaze::operator= (MyMaze &&maze){//оператор присваивания перемещением
        if (this == &maze)
            return *this;
            
        if (m_grid){
            for(int i = 0; i < m_height; i++){
                delete[] m_grid[i];
            }
            delete[] m_grid;
        }
            
        m_height = maze.m_height;
		m_width = maze.m_width;
        m_grid = maze.m_grid;
            
        maze.m_grid = nullptr;
            
        return *this;
    }
    
    MyMaze& MyMaze::operator= (const MyMaze &maze){//оператор присваивания копированием
        if (this == &maze)
            return *this;
            
        if (m_grid){
            for(int i = 0; i < m_height; i++){
                delete[] m_grid[i];
            }
            delete[] m_grid;
        }
            
        m_height = maze.m_height;
		m_width = maze.m_width;
		m_grid = new MyCell*[m_height];
		for (int i = 0; i < m_height; i++){
            m_grid[i] = new MyCell[m_width];
            for (int j = 0; j < m_width; j++)
				m_grid[i][j] = maze.m_grid[i][j];
		}
            
        return *this;
    }
    
    int MyMaze::checkNeighbours(int x, int y, int* &cells){//получает координаты клетки и массив для записи возможных направлений из этой клетки. проверяет соседей клетки на поссещённость. Если они непосещены, записывает их направление в массив и увеличивет счётчик направлений на 1. Возвращает количество непосещённых соседей клетки. Соседями называются клетки с индексом отличным только по вертикали или горизонтали от индекса входной клетки на 2.
        int count = 0;
        int cells_arr[4];
        if ((y-2 >= 0) && (this->m_grid[y-2][x].getAttendance() == 0)){
            cells_arr[count] = 1;//север
            count ++;
        }
        if ((x+2 < this->m_width) && (this->m_grid[y][x+2].getAttendance() == 0)){
            cells_arr[count] = 2;//восток
            count ++;
        }
        if ((y+2 < m_height) && (this->m_grid[y+2][x].getAttendance() == 0)){
            cells_arr[count] = 3;//юг
            count ++;
        }
        if ((x-2 >= 0) && (this->m_grid[y][x-2].getAttendance() == 0)){
            cells_arr[count] = 4;//запад
            count ++;
        }
            
        if (count == 0)
            return 0;
            
        for(int i = 0; i < count; i++)
            cells[i] = cells_arr[i];
        return count;
    } 
        
    void MyMaze::makeMaze(CellStack &stack){//Рекурсивная функция генерации лабиринта. Схожа с обходом в глубину в графе. Полчает на вход стек с клетками, если он пуст завершает выполнение (припервом вызове стек не пуст). Проверяет верхний элемент стека на наличие непосещённых соседей. Если их нет удаляет верхний элемент стека и вызывает себя от изменённого стека. Если есть - выбирает случайного соседа, соеденяет текущую клетку с эти соседом, добавляет соседа в стек и вызывает себя от изменённого стека.
        if(stack.getLength() == 0){
            return;
        }
            
        MyCell cell = stack.Top();
        int x = 0;
        int y = 0;
        int* cells = new int[4];//массив направлений
        int direction;
            
        cell.getCoordinates(x,y);
        int check = checkNeighbours(x, y, cells);            

        if (check == 0){
            stack.Remove();
            delete[] cells;
            makeMaze(stack);
            return;
        }
            //srand(time(NULL));
        direction = rand() % check;//генерация случайного направления
        switch (cells[direction]){
            case 1:
                this->m_grid[y-1][x].setData(1, STATE_GROUND);
                stack.Push(this->m_grid[y-2][x]);
                this->m_grid[y-2][x].setAttendance();
                break;
            case 2:
                 this->m_grid[y][x+1].setData(1, STATE_GROUND);
                 stack.Push(this->m_grid[y][x+2]);
                 this->m_grid[y][x+2].setAttendance();
                 break;
            case 3:
                 this->m_grid[y+1][x].setData(1, STATE_GROUND);
                 stack.Push(this->m_grid[y+2][x]);
                 this->m_grid[y+2][x].setAttendance();
                 break;
            case 4:
                 this->m_grid[y][x-1].setData(1, STATE_GROUND);
                 stack.Push(this->m_grid[y][x-2]);
                 this->m_grid[y][x-2].setAttendance();
                 break;
        }
        delete[] cells;
        makeMaze(stack);
        return;
    }
    
    void MyMaze::setStartFinish(int xs, int ys, int xf, int yf){//устанавливает точеи старта и финиша
        m_grid[ys][xs].setData(1,STATE_START);
        m_grid[yf][xf].setData(1,STATE_FINISH);
    }
    
    void MyMaze::prepareForMaze(int x, int y, int xs, int ys, int xf, int yf){//получает координаты стартовой клетки помещает её в стек, отмечая её помеченной и запускает рекурсивную функцию генерации лабиринта.
         CellStack stack(m_width*m_height/2);
         stack.Push(m_grid[y][x]);
         m_grid[y][x].setAttendance();
         makeMaze(stack);
         setStartFinish(xs, ys, xf, yf);
    }
    
    void MyMaze::print(){//выводит лабиринт
        for (int i = 0; i < m_height; i++){
            for (int j = 0; j < m_width; j++){
                m_grid[i][j].print();
            }
            cout << "\n";
        }
    }

	MyMaze::~MyMaze(){
		for(int i = 0; i < m_height; i++){
			delete[] m_grid[i];
		}
		delete[] m_grid;
	}