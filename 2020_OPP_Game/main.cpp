//g++  7.4.0

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
        }

        void setData(int set_passable, const char* set_type){//установка параметров проходимости и типа клетки
            m_passable = set_passable;
            m_type = set_type;
        }
    
        void setCoordinates(int set_x, int set_y){
            m_x = set_x;
            m_y = set_y;
        }
    
        void getCoordinates(int &get_x, int &get_y){
            get_x = this->m_x;
            get_y = this->m_y;
        }
        
        void printData(){
            std::cout << this->m_passable << " " << this->m_type << "\n"; 
        }
        
        void print(){
            cout << this->m_passable;
        }
        
        void setAttendance(){//установка параметра посещённости
            m_touched = 1;
        }
    
        int getAttendance(){//получение значения параметра посещённости
            return this->m_touched;
        }
		
		~MyCell(){
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
        
        void Push(MyCell &cell){//добавления клетки в стек            
			m_data[m_length] = cell;
            m_length++;
        }
    
        MyCell* Top(){//получение верхего элемента стека
            return &(m_data[m_length-1]);
        }
    
        int getLength(){//получение количества элементов в стеке
            return this->m_length;
        }
           
        void Remove(){//удаление верхнего элемента
            m_length--;
        }
    
        ~CellStack(){//деструктор; очищает выделенную память
            delete[] m_data;
			cout << "The end!\n";
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
            
            cells = new int[count];
            for(int i = 0; i < count; i++)
                cells[i] = cells_arr[i];
            return count;
        } 
        
        void makeMaze(CellStack &stack){//Рекурсивная функция генерации лабиринта. Схожа с обходом в глубину в графе. Полчает на вход стек с клетками, если он пуст завершает выполнение (припервом вызове стек не пуст). Проверяет верхний элемент стека на наличие непосещённых соседей. Если их нет удаляет верхний элемент стека и вызывает себя от изменённого стека. Если есть - выбирает случайного соседа, соеденяет текущую клетку с эти соседом, добавляет соседа в стек и вызывает себя от изменённого стека.
			//cout << stack.getLength() << "\n";
            if(stack.getLength() == 0){
                return;
            }
            
            MyCell* cell = stack.Top();
            int x = 0;
            int y = 0;
            int* cells;//массив направлений
            int direction;
            
            cell->getCoordinates(x,y);
            int check = checkNeighbours(x, y, cells);            

            if (check == 0){
                stack.Remove();
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
            makeMaze(stack);
            return;
        }
    
        void prepareForMaze(int x, int y){// получает координаты стартовой клетки помещает её в стек, отмечая её помеченной и запускает рекурсивную функцию генерации лабиринта.
            CellStack stack(m_width*m_height/2);
            stack.Push(m_grid[y][x]);
            m_grid[y][x].setAttendance();
            makeMaze(stack);
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

class MyInterface{
	private:
};		
		void getStartCoordinates(int &x, int &y){//получает координаты точки старта с консоли
			cout << "Введите координаты точки старта:\n";
			cin >> x >> y;
		}
};

int main()
{
    MyMaze maze(21,21);
	int x,y;
	//maze.getStartCoordinates(x, y);
    maze.prepareForMaze(1, 1);
    //maze.checkNeighbours(1, 1, &cells);
    //cout << "\n";
    maze.print();
}
