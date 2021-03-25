#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

template <class T>
int getData(T* &arr, ifstream& fin){
	int size = 0;
	int mem_size = 0;

	while(1){
		if(size == mem_size){
			mem_size += 10;
			T* new_arr = new T[mem_size];
			for(int i = 0; i < size; i++){
				new_arr[i] = arr[i];
			}
			delete[] arr;
			arr = new_arr;
		}

		if(fin.eof()){
			return size;
		}

		fin >> arr[size];
		size += 1;
	}

	return size;
}

template <class T>
void Sort(T* &arr, int size, ofstream& fout){
	T cur = 0;
	int j = 0;
	for(int i = 1; i < size; i++){
		cur = arr[i];
		j = i-1;

		cout << "Sorted part of array: ";
		fout << "Sorted part of array: ";
		for(int k = 0; k <= j; k++){
			cout << "\033[32m" << arr[k] << ' ';
		}
		cout << "\033[0mCurent elemrnt is " << "\033[33m" << cur << ' ' << "\033[0mUnsorted part of array: ";
		fout << "Curent elemrnt is " << cur << ' ' << "Unsorted part of array: ";
		for(int k = i+1; k < size; k++){
			cout << "\033[36m" << arr[k] << ' ';
			fout << arr[k] << ' ';
		}
		cout << "\033[0m\nCurrent index is " << i << '\n';
		fout << "\nCurrent index is " << i << '\n';

		while(arr[j] > cur && j >= 0){
			cout << "\033[32m" << arr[j] << "\033[0m at positon " << j << " is more than \033[33m" << cur << "\033[0m\n";
			fout << arr[j] << " at positon " << j << " is more than " << cur << "\n";
			arr[j+1] = arr[j];
			j -= 1;
		}
		if(j >= 0){
			cout << "\033[32m" << arr[j] << "\033[0m at positon " << j << " is less or equal than \033[33m" << cur << "\033[0m. Element insert into position with index " << j+1 << '\n';
			fout << arr[j] << " at positon " << j << " is less or equal than " << cur << ". Element insert into position with index " << j+1 << '\n';
		}
		else{
			cout << "Start of array nave been reached. \033[33m" << cur << "\033[0m is insert into the start of array.\n";
			fout << "Start of array nave been reached. " << cur << " is insert into the start of array.\n";
		}

		arr[j+1] = cur;

		cout << "Current status of array: ";
		fout << "Current status of array: ";
		for(int k = 0; k < size; k++){
			cout << arr[k] << ' ';
			fout << arr[k] << ' ';
		}
		cout << "\n\n";
		fout << "\n\n";
	}
}

template <class T>
class Node{
	private:
		T m_value;
		int m_next;
	public:
		Node(T value = 0, int next = -1): m_value(value), m_next(next){
		}

		void setValue(T value){
			m_value = value;
		}

		T getValue(){
			return m_value;
		}

		void setNext(int next){
			m_next = next;
		}

		int getNext(){
			return m_next;
		}
};

template <class T>
class List{
	private:
		Node<T>* m_head = nullptr;
		int head = 0;
		int m_size = 0;
		int m_memory_size = 0;
	public:
		List(){
			m_head = nullptr;
		}

		void addNode(T value){
			if(!m_head){
				head = 0;
				m_head = new Node<T>[10];
				m_head[0].setValue(value);
				m_size += 1;
				m_memory_size = 10;
				return;
			}

			if(m_size == m_memory_size){
				m_memory_size += 10;
				Node<T>* new_arr = new Node<T>[m_memory_size];
				for(int i = 0; i < m_size; i++){
					new_arr[i] = m_head[i];
				}
				delete[] m_head;
				m_head = new_arr;
			}

			int cur = 0;
			while(m_head[cur].getNext() != -1){
				cur += 1;
			}
			m_head[cur].setNext(m_size);;
			m_head[m_size].setValue(value);
			m_size += 1;
		}

		void makeList(T* &arr, int size){
			for(int i = 0; i < size; i++){
				addNode(arr[i]);
			}
		}

		void printList(ofstream& fout){
			int cur = head;
			while(cur != -1){
				cout << m_head[cur].getValue() << ' ';
				fout << m_head[cur].getValue() << ' ';
				cur = m_head[cur].getNext();
			}
			cout << '\n';
			fout << '\n';
		}

		void sort(ofstream& fout){
			int precur = head;
			int cur = m_head[precur].getNext();
			int comp = head;
			int precomp = head;
			while(cur != -1){
				m_head[precur].setNext(m_head[cur].getNext());
				m_head[cur].setNext(-1);
				//writeLog()

				while(comp != -1 && m_head[comp].getValue() < m_head[cur].getValue()){
					precomp = comp;
					comp = m_head[comp].getNext();
				}

				if(comp == head){
					m_head[cur].setNext(comp);
					head = cur;
				}
				else{
					m_head[precomp].setNext(cur);
					m_head[cur].setNext(comp);
				}
				if(m_head[precur].getNext() == cur){
					precur = cur;
					cur = m_head[cur].getNext();
				}
				else{
					cur = m_head[precur].getNext();
				}
				comp = head;
				precomp = head;	
				//printList(fout);	
			}
		}

		~List(){
			delete[] m_head;
		}
};

int main(){
	double* arr = nullptr;
	ifstream fin("./test.txt");
	int size = getData(arr, fin);
	ofstream fout("./res.txt");
	fin.close();

	/*for(int i = 0; i < size; i++){
		cout << arr[i] << ' ';
	}
	cout << '\n';
*/
	List<double> list;
	list.makeList(arr, size);
	list.printList(fout);
	//Sort(arr, size, fout);
	list.sort(fout);
	list.printList(fout);
	
	for(int i = 0; i < size; i++){
		cout << arr[i] << ' ';
	}
	cout << '\n';

	fout.close();

	return 0;
}
