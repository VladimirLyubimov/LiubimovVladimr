//Mady by Vladimir Lyubimov, ETU 2020.
#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class MyCell{//класс клетки
    private:
        int m_passable;//проходимость клетки
        const char* m_type;//её вид (стена, обычная клетка и тд.)
        int m_touched;//посещенали клетка при генерации лабиринта
        int m_x;
        int m_y;
    public:
        MyCell(){
            m_passable = 0;
            m_type = "fence";
            m_touched = 0;
			//cout << "Made!\n";
        }

        MyCell(const MyCell &cell){//конструктор копирования
            m_passable = cell.m_passable;
            m_type = cell.m_type;
            m_touched = cell.m_touched;
            m_x = cell.m_x;
            m_y = cell.m_y;
            //cout << "S_Made!\n";
        }
    
        void setData(int set_passable, const char* set_type){//установка параметров проходимости и типа клетки
            m_passable = set_passable;
            m_type = set_type;
        }
    
        void setCoordinates(int set_x, int set_y){//установка координат клетки
            m_x = set_x;
            m_y = set_y;
        }
    
        void getCoordinates(int &get_x, int &get_y){
            get_x = this->m_x;
            get_y = this->m_y;
        }
        
        void print(){
			if (m_type == "fence"){
            	cout << "@";
				return;
			}
			if (m_type == "ground"){
				cout << " ";
				return;
			}
            if (m_type == "start"){
				cout << "S";
				return;
			}
            if (m_type == "finish"){
				cout << "F";
				return;
			}
        }
        
        void setAttendance(){//установка параметра посещённости
            m_touched = 1;
        }
    
        int getAttendance(){//получение значения параметра посещённости
            return this->m_touched;
        }
		
		~MyCell(){
			//cout << "Destruction!\n";
		}
};

class CellStack{//стек клеток; необходим для генерации лабиринта; реализованы только необходимые методы
    private:
        MyCell* m_data;
        int m_length;
    public:
        CellStack(int size){
            m_data = new MyCell[size];
            m_length = 0;
        }
        
        void Push(MyCell cell){//добавления клетки в стек            
			m_data[m_length] = cell;
            m_length++;
        }
    
        MyCell Top(){//получение верхего элемента стека
            return m_data[m_length-1];
        }
    
        int getLength(){//получение количества элементов в стеке
            return this->m_length;
        }
           
        void Remove(){//удаление верхнего элемента
            m_length--;
        }
    
        ~CellStack(){//деструктор; очищает выделенную память
            delete[] m_data;
			//cout << "The end!\n";
        }
};

class MyMaze{//класс игрового поля-лабиринта
    private:
        MyCell** m_grid;
        int m_width;
        int m_height;
    public:
        MyMaze(int set_x, int set_y){//Создаём заготовку под лабиринт. Все клетки, у которых обе координаты нечётны объявляются проходимыми, остальнные стенами.
            m_width = set_x;
            m_height = set_y;
            m_grid = new MyCell*[m_height];
            for (int i = 0; i < m_height; i++){
                m_grid[i] = new MyCell[m_width];
                for (int j = 0; j < m_width; j++){
                    if ((i%2 == 1) && (j%2 == 1))
                        m_grid[i][j].setData(1, "ground");
                    m_grid[i][j].setCoordinates(j,i);
                }
            }
        }

		MyMaze(const MyMaze &maze){//конструктор копирования
			m_height = maze.m_height;
			m_width = maze.m_width;
			m_grid = new MyCell*[m_height];
			for (int i = 0; i < m_height; i++){
                m_grid[i] = new MyCell[m_width];
                for (int j = 0; j < m_width; j++)
					m_grid[i][j] = maze.m_grid[i][j];
			}
		}
    
        MyMaze(MyMaze &&maze){//конструктор перемещения
            m_height = maze.m_height;
			m_width = maze.m_width;
            m_grid = maze.m_grid;
            
            maze.m_grid = nullptr;
        }
    
        MyMaze& operator= (MyMaze &&maze){//оператор присваивания перемещением
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
    
        MyMaze& operator= (const MyMaze &maze){//оператор присваивания копированием
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
    
        int checkNeighbours(int x, int y, int* &cells){//получает координаты клетки и массив для записи возможных направлений из этой клетки. проверяет соседей клетки на поссещённость. Если они непосещены, записывает их направление в массив и увеличивет счётчик направлений на 1. Возвращает количество непосещённых соседей клетки. Соседями называются клетки с индексом отличным только по вертикали или горизонтали от индекса входной клетки на 2.
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
            
            //cells = new int[count];
            for(int i = 0; i < count; i++)
                cells[i] = cells_arr[i];
            return count;
        } 
        
        void makeMaze(CellStack &stack){//Рекурсивная функция генерации лабиринта. Схожа с обходом в глубину в графе. Полчает на вход стек с клетками, если он пуст завершает выполнение (припервом вызове стек не пуст). Проверяет верхний элемент стека на наличие непосещённых соседей. Если их нет удаляет верхний элемент стека и вызывает себя от изменённого стека. Если есть - выбирает случайного соседа, соеденяет текущую клетку с эти соседом, добавляет соседа в стек и вызывает себя от изменённого стека.
			//cout << stack.getLength() << "\n";
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
                    this->m_grid[y-1][x].setData(1, "ground");
                    stack.Push(this->m_grid[y-2][x]);
                    this->m_grid[y-2][x].setAttendance();
                    break;
                case 2:
                    this->m_grid[y][x+1].setData(1, "ground");
                    stack.Push(this->m_grid[y][x+2]);
                    this->m_grid[y][x+2].setAttendance();
                    break;
                case 3:
                    this->m_grid[y+1][x].setData(1, "ground");
                    stack.Push(this->m_grid[y+2][x]);
                    this->m_grid[y+2][x].setAttendance();
                    break;
                case 4:
                    this->m_grid[y][x-1].setData(1, "ground");
                    stack.Push(this->m_grid[y][x-2]);
                    this->m_grid[y][x-2].setAttendance();
                    break;
            }
            delete[] cells;
            makeMaze(stack);
            return;
        }
    
        void setStartFinish(int xs, int ys, int xf, int yf){//устанавливает точеи старта и финиша
            m_grid[ys][xs].setData(1,"start");
            m_grid[yf][xf].setData(1,"finish");
        }
    
        void prepareForMaze(int x, int y, int xs, int ys, int xf, int yf){//получает координаты стартовой клетки помещает её в стек, отмечая её помеченной и запускает рекурсивную функцию генерации лабиринта.
            CellStack stack(m_width*m_height/2);
            stack.Push(m_grid[y][x]);
            m_grid[y][x].setAttendance();
            makeMaze(stack);
            setStartFinish(xs, ys, xf, yf);
        }
    
        void print(){//выводит лабиринт
            for (int i = 0; i < m_height; i++){
                for (int j = 0; j < m_width; j++){
                    m_grid[i][j].print();
                }
                cout << "\n";
            }
        }

		~MyMaze(){
			for(int i = 0; i < m_height; i++){
				delete[] m_grid[i];
			}
			delete[] m_grid;
		}
};

class MyInterface{//класс реализующий примитивный консольный интерфейс
	public:		
		void getStartOfGenerationCoordinates(int &x, int &y){//получает координаты точки старта генерации с консоли
			cout << "Введите координаты точки старта генерации в формате x<пробел>y:\n";
			cin >> x >> y;
		}
		
		void getMazeSize(int &x, int &y){//получение линейных размеров лабиринта
			cout << "Введите линейнные размеры лабиринтав формате x<пробел>y:\n";
			cin >> x >> y;
		}
    
        void getStartAndFinish(int &xs, int &ys, int &xf, int &yf){//получает точки старта и финиша
            cout << "Сейчас вам будет предложено ввести координаты точек старта и финиша в формате x<пробел>y. Если\n";
            cout << "Введите координаты точки старта:\n";
			cin >> xs >> ys;
            
            cout << "Введите координаты точки финиша:\n";
			cin >> xf >> yf;
        }
        
		void printMaze(MyMaze maze){
			maze.print();
		}
};

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
    //maze.checkNeighbours(1, 1, &cells);
    //cout << "\n";
    //maze.print();
}
