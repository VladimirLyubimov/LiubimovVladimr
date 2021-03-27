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
		int* m_arr = nullptr;
		int m_root = 0;
		int m_size = 0;
		int m_arr_size = 0;//размер массива
		int m_mem_size = 0;
		int m_d = 2;

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
			for(int i = root*m_d+1; i <= root*m_d + m_d && i < m_size; i++){
				if(max == -1){
					max = i;
				}
				if(m_arr[i] > m_arr[max]){
					max = i;
				}
			}
			return max;
		}

		int findMax(int root){//поиск индекса максимального элемента среди вершины и потомков
			int max = root;
			for(int i = root*m_d+1; i <= root*m_d + m_d && i < m_size; i++){
				if(m_arr[i] > m_arr[max]){
					max = i;
				}
			}
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
				if(m_arr[root] > m_arr[findMax(root)]){
					return;
				}
 
				int n_root = findMax(root);
				if(n_root == root){
					return;
				}
				int c = m_arr[root];
				m_arr[root] = m_arr[n_root];
				m_arr[n_root] = c;
				root = n_root;
			}
		}

		void makeHeap(){
			int i = m_size/m_d;
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

		void upwardSift(){
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

			//i -= 1;
			//for(int j  = 0; j < i; j++){
				//cout << way[j] << '\n';
			//}
			while(m_arr[m_root] > m_arr[cur]){
				cur = way[i-1];
				i -= 1;
			}
			//cout << cur << '\n';
			buf = m_arr[cur];
			m_arr[cur] = m_arr[m_root];
			i -= 1;
			int add_buf = buf;
			//m_arr[cur] = buf;
			while(cur > m_root){
				cur = way[i];
				//cout << m_arr[cur] << '\n';
				buf = m_arr[cur];
				//m_arr[way[i-1]] = m_arr[cur];
				m_arr[cur] = add_buf;
				add_buf = buf;
				i -= 1;
				//cur = way[i];
				//cout << i << '\n';
			}
			//cout << way[length-2] << '\n';
			/*for(int i = length-2; i > 0; i--){
				if(m_arr[way[i]] > m_arr[way[i-1]]){
					cout << way[i] << ' ' << way[i-1] << '\n';
					buf = m_arr[way[i]];
					m_arr[way[i]] = m_arr[way[i-1]];
					m_arr[way[i-1]] = buf;
				}
				//return;
				//printHeap();
			}*/
		}

		void upwardSiftSort(){
			while(m_size){;
				dragMax();
				upwardSift();
				//return;
				//printHeap();
				printAsArr();
				//cout << "\n\n\n";
			}
		}

		void printAsArr(){
			for(int i = 0; i < m_arr_size; i++){
				cout << m_arr[i] << ' ';
			}
			cout << '\n';
		}

		void printNode(int node_value, int step){
			for(int i = 0; i < step; i++){
				cout << ' ';
			}

			cout.setf(ios::left);
			cout.width(4);
			cout << node_value;
			cout.unsetf(ios::left);

			//cout << step << '\n';
			for(int i = 0; i < step; i++){
				cout << ' ';
			}
		}

		void printHeap(){
			int lev = 0;
			int sep = 0;
			int height = calcHeight();
			//cout << height << '\n';
			//cout << m_size << '\n';
			int step = 0;
			for(int i = 0; i < m_size; i++){
				step = int(3*2*int(pow(double(m_d),double(height-1)))/(2*int(pow(double(m_d),double(lev))))-2);
				//cout << lev << ' ' << step << '\n';
				if(lev == 0){
					printNode(m_arr[i], step);
					lev += 1;
					cout << '\n';
					continue;
				}
				printNode(m_arr[i], step);

				if(i%((int)(double(1.0-pow(double(m_d), double(lev+1)))/double(1-m_d))-1) == 0 || m_d == 1){
					lev += 1;
					cout << '\n';
				}
			}
			cout << '\n';
		}

		int goToMaxLeaf(int* &way){//спускаемся до листа, для каждой вершины выбирая максимального потомка
			int root =	m_root;
			int length = 1;
			int i = 0;
			way[i] = root;
			while(root*m_d+1 < m_size){
				length += 1;
				i += 1;
				root = findMaxLeaf(root);
				way[i] = root;
			}

			return length;
		}

		int getHeight(){
			return calcHeight();
		}

		~Dheap(){
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

	//Dheap heap(arr, 0, 15, 2);
	Dheap heap(fin);
	heap.printHeap();
	heap.makeHeap();
	heap.printHeap();
	//heap.printHeap();
	//heap.printAsArr();
	//heap.dragMax();
	heap.upwardSiftSort();
	heap.printHeap();
	heap.printAsArr();
	
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
