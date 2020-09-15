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
            //m_data[m_length].setAttendance();
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
        }
};

class MyMaze{//класс игрового поля-лабиринта
    private:
        MyCell** m_grid;
        int m_width;
        int m_height;
    public:
        MyMaze(int set_x, int set_y){
            m_width = set_x;
            m_height = set_y;
            m_grid = new MyCell*[m_height];
            for (int i = 0; i < m_height; i++){
                m_grid[i] = new MyCell[m_width];
                for (int j = 0; j < m_width; j++){
                    if ((i%2 == 1) && (j%2 == 1))
                        m_grid[i][j].setData(1, "ground");
                    //m_grid[i][j].print();
                    m_grid[i][j].setCoordinates(j,i);
                }
                //cout << "\n";
            }
        }
    
        int checkNeighbours(int x, int y, int* &cells){
            int count = 0;
            int cells_arr[4];
            if ((y-2 >= 0) && (this->m_grid[y-2][x].getAttendance() == 0)){
                cells_arr[count] = 1;
                count ++;
            }
            if ((x+2 < this->m_width) && (this->m_grid[y][x+2].getAttendance() == 0)){
                cells_arr[count] = 2;
                count ++;
            }
            if ((y+2 < m_height) && (this->m_grid[y+2][x].getAttendance() == 0)){
                cells_arr[count] = 3;
                count ++;
            }
            if ((x-2 >= 0) && (this->m_grid[y][x-2].getAttendance() == 0)){
                cells_arr[count] = 4;
                count ++;
            }
            
            if (count == 0)
                return 0;
            
            cells = new int[count];
            for(int i = 0; i < count; i++)
                cells[i] = cells_arr[i];
            return count;
        } 
        
        void makeMaze(CellStack &stack){
            //this->print();
            //cout << "\n";
            if(stack.getLength() == 0){
                stack.~CellStack();
                return;
            }
            
            MyCell cell = stack.Top();
            int x = 0;
            int y = 0;
            int* cells;
            int direction;
            
            cell.getCoordinates(x,y);
            int check = checkNeighbours(x, y, cells);
            
            if (check == 0){
                stack.Remove();
                makeMaze(stack);
                return;
            }
            //int a = 1634517381641453*1450+6131333;
            //srand(time(NULL));
            //srand(a);
            direction = rand() % check;
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
    
        void prepareForMaze(){
            CellStack stack(25);
            stack.Push(m_grid[1][1]);
            m_grid[1][1].setAttendance();
            makeMaze(stack);
        }
    
        void print(){
            for (int i = 0; i < m_height; i++){
                for (int j = 0; j < m_width; j++){
                    m_grid[i][j].print();
                }
                cout << "\n";
            }
        }
};

int main()
{
    MyMaze maze(21,11);
    maze.prepareForMaze();
    //maze.checkNeighbours(1, 1, &cells);
    cout << "\n";
    maze.print();
}
