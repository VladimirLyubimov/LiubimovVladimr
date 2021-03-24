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
	int cur = 0;
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
		Node* m_next;
	public:
		Node(T value, Node* next = nullptr): m_value(value), m_next(next){
		}

		void setValue(T value){
			m_value = value;
		}

		T getValue(){
			return m_value;
		}

		void setNext(Node* next){
			m_next = next;
		}

		Node* getNext(){
			return m_next;
		}
};

template <class T>
class List{
	private:
		T* m_head = nullptr;
		T* m_cur = nullptr;
	public:
		List(){
			m_head = nullptr;
			m_cur = nullptr;
		}

		void addNode(T value){
			m_cur->setNext(new Node<T>(value));
			if(!m_head){
				m_head = m_cur;
			}
			m_cur = m_cur->setNext;
		}

		void makeList(T* &arr, int size){
			for(int i = 0; i < size; i++){
				addNode(arr[i]);
			}
		}

		void printList(ofstream& fout){
			T* cur = m_head;
			while(cur){
				cout << cur->getValue() << ' ';
				fout << cur->getValue() << ' ';
				cur = cur->getNext();
			}
			cout << '\n';
			fout << '\n';
		}

		void Sort(){
			T* precur = m_head;
			T* cur = precur->getNext();
			T* comp = m_head;
			while(cur){
				precur->setNexy(cur->getNext());
				cur->setNext(nullptr);
				

			}
		}

		~List(){
			T* next;
			while(m_head){
				next = m_head->getNext();
				delete m_head;
				m_head = next;
			}
		}
};

int main(){
	int* arr = nullptr;
	ifstream fin("./test.txt");
	int size = getData(arr, fin);
	ofstream fout("./res.txt");
	fin.close();

	for(int i = 0; i < size; i++){
		cout << arr[i] << ' ';
	}
	cout << '\n';

	//Sort(arr, size, fout);

	for(int i = 0; i < size; i++){
		cout << arr[i] << ' ';
	}
	cout << '\n';

	fout.close();

	return 0;
}
