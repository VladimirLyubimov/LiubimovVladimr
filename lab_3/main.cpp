#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

class Node{//класс реализующий узел
	private:
		char m_data;//значение узла
		int m_left;
		int m_right;
	public:
		Node(char data = 0, int left = -1, int right = -1): m_data(data), m_left(left), m_right(left){
		}
		
		~Node(){}
		
		void setLeft(int left){
			m_left = left;
		}
		
		void setRight(int right){
			m_right = right;
		}
		
		void setData(char data){
			m_data = data;
		}
		
		int getLeft(){
			return m_left;
		}
	
		int getChild(){
			return m_right;
		}
		
		char getData(){
			return m_data;
		}	
};

void writeLog(int step, ofstream& fout, string message){//логирование промежуточных и итоговых данных
	for(int i = 0; i < step; i++){
		fout << "\t";
		cout << "\t";
	}
	fout << message;
	cout << message;
}

void makeLogMessage(string& message, const char* st_data, char c_data, const char* end){//создание с++ строки для логирования
	message += st_data;
	message += c_data;
	message += end;
}

class NodeStack{
	private:
		Node* m_data = nullptr;
		int m_size = 0;
		int m_memory_size = 0;
	public:
		NodeStack(){
		}

		void add(Node node){
			if(m_memory_size == m_size){
				m_memory_size += 10;
				Node* new_data = new Node[m_memory_size];
				for(int i = 0; i < m_size; i++){
					new_data[i] = m_data[i];
				}
				delete[] m_data;
				m_data = new_data;
			}

			m_data[m_size] = node;
			m_size += 1;
		}

		Node pop(){
			return m_data[m_size];
		}
};

class BinTree{
	private:
		Node* m_data = nullptr;
		int m_size = 0;
		int m_memory_size = 0;
	public:
		BinTree(){
		}

		int addNode(char value, int parent, char side){
			if(m_memory_size == m_size){
				m_memory_size += 10;
				Node* new_data = new Node[m_memory_size];
				for(int i = 0; i < m_size; i++){
					new_data[i] = m_data[i];
				}
				delete[] m_data;
				m_data = new_data;
			}
			
			m_data[m_size].setData(value);
			switch (side){
				case 'l':
					m_data[parent].setLeft(m_size);
					break;
				case 'r':
					m_data[parent].setRight(m_size);
					break;
				default:
					break;
			}
			m_size += 1;
			return m_size - 1;
		}

		void makeTree(string tree, int& i, int parent){
			int cur = parent;
			while(i < tree.size()){
				switch (tree[i]){
					case '(':
						i += 1;
						makeTree(tree, i, parent);
						break;
					case ')':
						i += 1;
						return;
					default:
						if(!m_data){
							cur = addNode(tree[i], -1, 0);
							i += 1;
							continue;
						}
						if(tree[i] == '|'){
							i += 1;
							continue;
						}
						if(tree[i-1] == '('){
							if(tree[i+1] == '(')
								parent = addNode(tree[i], cur, 'l');
							else
								addNode(tree[i], cur, 'l');
							i += 1;
						}
						if(tree[i-1] != '('){
							if(tree[i+1] == '(')
								parent = addNode(tree[i], cur, 'r');
							else
								addNode(tree[i], cur, 'r');
							i += 1;
						}
				}
			}
		}

		void getPrintTree(string& tree, int parent, NodeStack stack){
			int cur = parent;
			//while()
		}

		~BinTree(){
			delete[] m_data;
		}
};

int main(){
	BinTree tree;
	int root = 0;
	tree.makeTree("(f(h)(j))", root, 0);
	return 0;
}
