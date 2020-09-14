//g++  7.4.0

#include <iostream>

using namespace std;

class MyCell{
    private:
        int passable;
        const char* type;
        int touched;
    public:
        MyCell(){
            passable = 0;
            type = "fence";
            touched = 0;
        }
        void setData(int set_passable, const char* set_type){
            passable = set_passable;
            type = set_type;
            return;
        }
        
        void printData(){
            std::cout << this->passable << " " << this->type << "\n"; 
        }
        
        void print(){
            cout << this->passable;
        }
        
        void setAttendance(){
            touched = 1;
        }
    
        int getAttendance(){
            return this->touched;
        }
};

class CellStack{
    private:
        MyCell* data;
        int length;
    public:
        CellStack(int size){
            data = new MyCell[size];
            length = 0;
        }
        
        void Add(MyCell cell){
            data[length] = cell;
            length++;
        }
    
        MyCell top(){
            length--;
            return data[length];
        }
    
        ~CellStack(){
            delete[] data;
        }
};

class MyMaze{
    private:
        MyCell** grid;
        int width;
        int height;
    public:
        MyMaze(int set_x, int set_y){
            width = set_x;
            height = set_y;
            grid = new MyCell*[height];
            for (int i = 0; i < height; i++){
                grid[i] = new MyCell[width];
                for (int j = 0; j < width; j++){
                    if ((i%2 == 1) && (j%2 == 1))
                        grid[i][j].setData(1, "ground");
                    grid[i][j].print();
                }
                cout << "\n";
            }
        }
    
        int checkNeighbours(int x, int y, int** cells){
            int res = 0;
            int count = 0;
            int cells_arr[4];
            if ((y-2 >= 0) && (this->grid[y-2][x].getAttendance() == 0)){
                cells_arr[count] = 1;
                count ++;
            }
        } 
        
        void makeMaze(){
            
        }
};

int main()
{
    MyMaze maze(11,11);
}
