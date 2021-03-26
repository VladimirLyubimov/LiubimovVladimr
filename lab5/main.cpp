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
		int m_d = 2;

	public:
		Dheap(int* arr = nullptr, int root = 0, int size = 0, int d = 2): m_arr(arr), m_root(root), m_size(size), m_d(d){
		}

		int findMaxLeaf(int root){
			int max = root;
			for(int i = root; i < m_size || i <= root + m_d; i++){
				if(m_arr[i] > m_arr[max]){
					max = i;
				}
			}
			return max;
		}

		void siftUp(int leaf){
			if(leaf == m_root || (leaf-1)/m_d < 0){
				return;
			}

			while(leaf != m_root && m_arr[leaf] > m_arr[(leaf-1)/m_d]){
				swap(m_arr[leaf], m_arr[(leaf-1)/m_d]);
				leaf = (leaf-1)/m_d;
				if(leaf < 0){
					return;
				}
			}
		}

		void siftDown(int root){
			while(root * m_d + 1 < m_size){
				if(m_arr[root] > m_arr[findMaxLeaf(root)]){
					return;
				}

				int c = m_arr[root]; 
				int n_root = findMaxLeaf(root);
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
		}

		void addElement(){}
		
		int dragMax(){
			int max = m_arr[m_root];
			m_arr[m_root] = m_arr[m_size-1];
			m_size -= 1;
			return max;
		}

		void printNode(int node_value, int step){
			for(int i = 0; i < step; i++){
				cout << '_';
			}
			cout.setf(ios::left);
			cout.width(4);
			cout << node_value;
			cout.unsetf(ios::left);
		}

		void printHeap(){
			int lev = 0;
			double height = floor(log(double(m_size))/log(double(m_d))) + 1;
			int step = int((6*pow(double(m_d),height-1)-6)/(2*pow(double(m_d),lev)));
			for(int i = 0; i < m_size; i++){
				if(lev == 0){
					printNode(m_arr[i], step + 1);
					lev += 1;
					step = step/m_d;
					cout << '\n';
					continue;
				}
				printNode(m_arr[i], step + 1);
				if(i%((int)(double(1.0-pow(double(m_d), double(lev+1)))/double(1-m_d))-1) == 0){
					lev += 1;
					step = step/m_d;
					cout << '\n';
				}
				//cout << m_arr[i] << ' ';
				//if(i%(m_d*lev) == 0){
					//lev += 1;
				//	cout << '\n';
				//}
			}
			cout << '\n';
		}

		~Dheap(){
			delete[] m_arr;
		}
};

int main(){
	int* arr = new int[10];
	ifstream fin("test.txt");
	if(!fin.is_open()){
		cout << "Opening file with test data failed!\n";
		return 0;
	}
	for(int i = 0; i < 10; i++){
		fin >> arr[i];
	}
	
	for(int i = 0; i < 10; i++){
		cout << arr[i] << ' ';
	}
	cout << '\n';

	Dheap heap(arr, 0, 10, 2);
	heap.makeHeap();
	heap.printHeap();
	return 0;
}
