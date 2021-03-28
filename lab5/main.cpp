#include <regex.h>
#include <string.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

class Dheap{
	private:
		int* m_arr = nullptr;//массив хранящий кучу
		int m_root = 0;//корень кучи
		int m_size = 0;//размер кучи
		int m_arr_size = 0;//размер массива
		int m_mem_size = 0;//размер кучи в памяти
		int m_d = 2;//порядок кучи; по умолчанию куча бинарная

	public:
		Dheap(int* arr = nullptr, int root = 0, int size = 0, int d = 2): m_root(root), m_size(size), m_d(d){//конструктор копирует полученный массив в массив вершин; пока в это ещё не d-арное дерево
			m_arr = new int[size];
			for(int i = 0; i < size; i++){
				m_arr[i] = arr[i];
			}
		}

		Dheap(ifstream &fin){//конструктор считывающий массив из входного файла
			m_size = 0;
			m_mem_size = 0;
			m_root = 0; 
			fin >> m_d;

			while(1){
				if(m_size == m_mem_size){
					m_mem_size += 10;
					int* new_arr = new int[m_mem_size];
					for(int i = 0; i < m_size; i++){
						new_arr[i] = m_arr[i];
					}
					delete[] m_arr;
					m_arr = new_arr;
				}

				if(fin.eof()){
					break;
				}

				fin >> m_arr[m_size];
				m_size += 1;
			}

			m_arr_size = m_size;
		}

		int calcHeight(){//высчитывает количество уровней в дереве
			int i = m_root;
			int height = 0;
			while(i < m_size){
				height += 1;
				i = i*m_d + 1;
			}
			return height;
		}

		int findMaxLeaf(int root){//поиск индекса максимального элемента среди потомков вершины
			int max = -1;
			int j = 0;
			int nodes[m_d+1];
			cout << "The value of root is " << m_arr[root] << "\n";
			nodes[j] = root;
			j += 1;
			printHeap(nodes, j);
			for(int i = root*m_d+1; i <= root*m_d + m_d && i < m_size; i++){
				if(max == -1){
					max = i;
					cout << m_arr[i] << " is first son, so it is new maximum value.\n";
					nodes[j] = i;
					j += 1;
					printHeap(nodes, j);					
					continue;
				}

				if(m_arr[i] > m_arr[max]){
					cout << m_arr[i] << " is more than current maximum value, which is " << m_arr[max] << '\n';
					max = i;
				}
				else{
					cout << m_arr[i] << " is less than current maximum value, which is " << m_arr[max] << '\n';
				}
				nodes[j] = i;
				j += 1;
				printHeap(nodes, j);
			}
			cout << "Summary, the value of maximal leaf is " << m_arr[max] << "\n";
			nodes[0] = max;
			printHeap(nodes, 1);
			return max;
		}

		int findMax(int root){//поиск индекса максимального элемента среди вершины и потомков
			int max = root;
			int j = 0;
			int nodes[m_d+1];
			cout << "The value of root is " << m_arr[root] << "\n";
			nodes[j] = root;
			j += 1;
			printHeap(nodes, j);
			for(int i = root*m_d+1; i <= root*m_d + m_d && i < m_size; i++){
				if(m_arr[i] > m_arr[max]){
					cout << m_arr[i] << " is more than current maximum value, which is " << m_arr[max] << '\n';
					max = i;
				}
				else{
					cout << m_arr[i] << " is less than current maximum value, which is " << m_arr[max] << '\n';
				}
				nodes[j] = i;
				j += 1;
				printHeap(nodes, j);
			}
			cout << "Summary, the value of maximal element of root and its leaf is " << m_arr[max] << "\n";
			nodes[0] = max;
			printHeap(nodes, 1);
			cout << "\n\n\n";
			return max;
		}

		void siftUp(int leaf){//просейка снизу-вверх
			if(leaf == m_root || (leaf-1)/m_d < 0){
				return;
			}

			while(leaf != m_root && m_arr[leaf] > m_arr[(leaf-1)/m_d] && m_arr[m_root] < m_arr[leaf]){
				int c = m_arr[leaf];
				m_arr[leaf] = m_arr[m_root];
				m_arr[m_root] = c;
				leaf = (leaf-1)/m_d;
				if(leaf < 0){
					return;
				}
			}
		}

		void siftDown(int root){//обыкновенная просейка сверху-вниз
			while(root * m_d + 1 < m_size){
 
				int n_root = findMax(root);

				if(m_arr[root] > m_arr[n_root]){
					return;
				}

				if(n_root == root){
					return;
				}
				int c = m_arr[root];
				m_arr[root] = m_arr[n_root];
				m_arr[n_root] = c;
				root = n_root;
			}
		}

		void makeHeap(){//получение кучи из массива за О(n) времени, где n - количетсво элементов в массиве
			int i = m_size/m_d;//элементы с большими индексами не имеют потомков, то есть они уже являются кучами
			while(i >= 0){
				siftDown(i);
				i -= 1;
			}
			m_arr_size = m_size;
		}
		
		void dragMax(){//удаляет вершину из кучи перенося её в конец массива предварительно заменив его последним элементом
			int max = m_arr[m_root];
			m_arr[m_root] = m_arr[m_size-1];
			m_arr[m_size-1] = max;
			m_size -= 1;
		}

		void upwardSift(){//восходящая просейка (модифицированная просейка снизу-вверх); спускаемся вниз по наибольшим вершинам, поднимаемся по этой ветке до первой вершины больше корня, сохраняем её, заменяем её корнем, сдвигаем ветку на один уровень вверх через буфферную переменную
			int buf;
			int cur = m_root;
			int way[calcHeight()];
			int i = 0;
			way[i] = m_root;
			i += 1;

			while(cur*m_d+1 < m_size){
				cur = findMaxLeaf(cur);
				way[i] = cur;
				i += 1;
			}

			if(m_arr[m_root] > m_arr[cur]){
				while(m_arr[m_root] > m_arr[cur]){
					cur = way[i-1];
					i -= 1;
				}
			}
			else{
				i -= 1;
				cur = way[i];
			}
			buf = m_arr[cur];
			m_arr[cur] = m_arr[m_root];
			i -= 1;
			int add_buf = buf;
			while(cur > m_root){
				cur = way[i];
				buf = m_arr[cur];
				m_arr[cur] = add_buf;
				add_buf = buf;
				i -= 1;
			}
		}

		void upwardSiftSort(){//сортировка с использованием восходящей просейки
			while(m_size){;
				dragMax();
				upwardSift();
			}
		}

		void siftDownSort(){//сортировка с использованием просейки сверху-вниз
			while(m_size){;
				dragMax();
				siftDown(m_root);
			}
		}

		void printAsArr(){//выводит кучу как массив
			for(int i = 0; i < m_arr_size; i++){
				cout << m_arr[i] << ' ';
			}
			cout << '\n';
		}

		void printNode(int node_value, int step, bool is_col){//выводит узел в консоль
			for(int i = 0; i < step; i++){
				cout << ' ';
			}

			if(is_col){
				cout << "\033[1;30;47m";
			}
			cout.setf(ios::left);
			cout.width(4);
			cout << node_value;
			cout.unsetf(ios::left);
			cout << "\033[0m";

			for(int i = 0; i < step; i++){
				cout << ' ';
			}
		}

		void printHeap(int* color_nodes, int col_size){//выводит кучу в консоль, как дерево
			int lev = 0;
			int sep = 0;
			int height = calcHeight();
			bool is_col = false;
			int j = 0;
			//cout << height << '\n';
			//cout << m_size << '\n';
			int step = 0;
			for(int i = 0; i < m_size; i++){
				step = int(3*2*int(pow(double(m_d),double(height-1)))/(2*int(pow(double(m_d),double(lev))))-2);
				
				is_col = false;
				if(j < col_size){
					if(i == color_nodes[j]){
						is_col = true;
						j += 1;
					}
				}
				//cout << lev << ' ' << step << '\n';
				if(lev == 0){
					printNode(m_arr[i], step, is_col);
					lev += 1;
					cout << '\n';
					continue;
				}
				printNode(m_arr[i], step, is_col);

				if(i%((int)(double(1.0-pow(double(m_d), double(lev+1)))/double(1-m_d))-1) == 0 || m_d == 1){
					lev += 1;
					cout << '\n';
				}
			}
			cout << "\n\n";
		}

		int goToMaxLeaf(int* &way){//спускаемся до листа, для каждой вершины выбирая максимального потомка
			cout << "Now we will find a route to the leaf which consist of the biggest sons.\n";
			int root =	m_root;
			int length = 1;
			int i = 0;
			way[i] = root;
			cout << "So the first node is root of the heap and its value is " << m_arr[root] << ". Itshas been added to the route.";
			while(root*m_d+1 < m_size){
				length += 1;
				i += 1;
				root = findMaxLeaf(root);
				way[i] = root;
				cout << "So node with value " << m_arr[root] << " has been added to the route.\n\n\n";
			}
			
			cout << "Eventually we have managed to get the route!\n";
			printHeap(way, length);
			return length;
		}

		int getHeight(){//возвращает высоту дерева
			return calcHeight();
		}

		~Dheap(){//деструктор; очищает память выделенную под массив-кучу
			delete[] m_arr;
		}
};


int main(){
	int* arr = new int[15];
	ifstream fin("test.txt");
	if(!fin.is_open()){
		cout << "Opening file with test data failed!\n";
		return 0;
	}

	Dheap heap(fin);
	heap.printHeap(nullptr, -1);
	heap.makeHeap();
	heap.printHeap(nullptr, -1);
	//int* way = new int[heap.getHeight()];
	//heap.goToMaxLeaf(way);
	//heap.printHeap();
	//heap.printAsArr();
	//heap.dragMax();
	//heap.upwardSiftSort();
	//heap.siftDownSort();
	heap.printHeap(nullptr, -1);
	//heap.printAsArr();
	
	//
	//heap.printHeap();
	//heap.upwardSift();
	//heap.printAsArr();
	//heap.printHeap();

	/*int* way = new int[heap.getHeight()];
	heap.goToMaxLeaf(way);
	for(int i = 0; i < heap.getHeight(); i++){
		cout << way[i] << ' ';
	}*/
	cout << '\n';
	return 0;
}
