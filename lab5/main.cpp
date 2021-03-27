#include <regex.h>
#include <string.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <algorithm> //for swap()

using namespace std;

class Dheap{
	private:
		int* m_arr = nullptr;
		int m_root = 0;
		int m_size = 0;
		int m_mem_size = 0;
		int m_d = 2;

	public:
		Dheap(int* arr = nullptr, int root = 0, int size = 0, int d = 2): m_root(root), m_size(size), m_d(d){//конструктор копирует полученный массив в массив вершин; пока в это ещё не d-арное дерево
			m_arr = new int[size];
			for(int i = 0; i < size; i++){
				m_arr[i] = arr[i];
			}
		}

		Dheap(ifstream &fin){//конструктор считывающий массив из входного
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

		int findMaxLeaf(int root){//поиск максимального листа
			int max = root;
			for(int i = root*m_d+1; i <= root*m_d + m_d && i < m_size; i++){
				if(m_arr[i] > m_arr[max]){
					max = i;
				}
			}
			return max;
		}

		void siftUp(int leaf){//просейка снизу-вверх с модификацией для восходящей просейки 
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
				if(m_arr[root] > m_arr[findMaxLeaf(root)]){
					return;
				}
 
				int n_root = findMaxLeaf(root);
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
				//printHeap();
				i -= 1;
			}
		}

		void addElement(){}
		
		int dragMax(){
			int max = m_arr[m_root];
			m_arr[m_root] = m_arr[m_size-1];
			m_size -= 1;
			return max;
		}

		void printNode(int node_value, int step, int& sep){
			for(int i = 0; i < step; i++){
				cout << ' ';
			}

			cout.setf(ios::left);
			cout << node_value;
			cout.unsetf(ios::left);

			if(sep == m_d){
				step -= 1;
			}
			for(int i = 0; i < step; i++){
				cout << ' ';
			}
			if(sep == m_d){
				cout << '|';
				sep = 0;
			}
		}

		void printHeap(){
			int lev = 0;
			int sep = 0;
			double height = floor(log(double(m_size-1))/log(double(m_d))) + 2;
			cout << m_size << '\n';
			int step = int((3*pow(double(m_d),height-1))/(2*pow(double(m_d),lev))+3*(height-1)*m_d);
			for(int i = 0; i < m_size; i++){
				if(lev == 0){
					printNode(m_arr[i], step, sep);
					lev += 1;
					step = step/m_d;
					cout << '\n';
					continue;
				}

				sep += 1;
				printNode(m_arr[i], step, sep);

				if(i%((int)(double(1.0-pow(double(m_d), double(lev+1)))/double(1-m_d))-1) == 0 || m_d == 1){
					lev += 1;
					step = step/m_d;
					sep = 0;
					cout << '\n';
				}

				//if(sep == m_d){
				//	sep = 0;
				//	continue;
				//}

				if(step == 0){
					cout << "|";
				}
			}
			cout << '\n';
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

	for(int i = 0; i < 15; i++){
		cout << arr[i] << ' ';
	}
	cout << '\n';

	//Dheap heap(arr, 0, 15, 2);
	Dheap heap(fin);
	heap.printHeap();
	heap.makeHeap();
	heap.printHeap();
	return 0;
}
