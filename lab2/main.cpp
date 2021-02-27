#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

class Node{
	private:
		char m_data;
		Node* m_next;
		Node* m_child;
	public:
		Node(char data = 0, Node* next = nullptr, Node* child = nullptr): m_data(data), m_next(next), m_child(child){			
		}
		
		~Node(){}
		
		void setNext(Node* next){
			m_next = next;
		}
		
		void setChild(Node* child){
			m_child = child;
		}
		
		void setData(char data){
			m_data = data;
		}
		
		Node* getNext(){
			return m_next;
		}
	
		Node* getChild(){
			return m_child;
		}
		
		char getData(){
			return m_data;
		}	
};

class H_list{
	private:
		Node* m_head;
	public:
		H_list(){
			m_head = nullptr;
		}
				
		void getPrintMessage(string& str, Node* cur){
			str += "(";
			while(cur){
				str += cur->getData();
				if(cur->getChild()){
					getPrintMessage(str, cur->getChild());
				}
				cur = cur->getNext();
			}
			str += ")";
		}
				
		Node* getHead(){
			return m_head;
		}
				
		int makeList(string& data, int i, Node* cur, int level){
			if(data == ""){
				m_head = new Node(0);
				cout << "The empty hierarchical created.\n";
				return 0;
			}
			
			while(i < data.size()){
				if(data[0] != '(' && !m_head){
					m_head = new Node(data[0]);
					cur = m_head;
					i += 1;
					cout << "The first element created. Its value is " << data[0] << "\n";
					continue;
				}
				
				if(data[i] == '(' && !m_head){
					i += 1;
					m_head = new Node(data[i]);
					cur = m_head;
					cout << "The first element created. Its value is " << data[i] << "\n";
					i += 1;
					continue;
				}
				
				if(data[i] == '(' && m_head){
					i += 1;
					cur->setChild(new Node(data[i]));
					i += 1;
					for(int j = 0; j < level; j++)
						cout << "\t";
					cout << "The building of new level of hierarchical list have been started. Recursion used.\n";
					i = makeList(data, i, cur->getChild(), level+1);
					continue;
				}
				
				if(data[i] == ')'){
					i += 1;
					for(int j = 0; j < level; j++)
						cout << "\t";
					cout << "Return to previos level of the list.\n";
					return i;
				}
				
				if(data[i] != ')' && data[i] != '('){
					for(int j = 0; j < level; j++)
						cout << "\t";
					cout << "The one more element created. Its value is " << data[i] << "\n";
					cur->setNext(new Node(data[i]));
					cur = cur->getNext();
					i += 1;
					continue;
				}
			}
			
			return 0;
		}
		
		void replaceAtom(char atom, char change, Node* cur){
			while(cur){
				if(cur->getChild()){
					replaceAtom(atom, change, cur->getChild());
				}
				
				if(cur->getData() == atom){
					cur->setData(change);
				}
				
				cur = cur->getNext();
			}
		}
		
		void clearSpace(Node* cur){
			Node* prev;
			while(cur){
				if(cur->getChild()){
					clearSpace(cur->getChild());
				}
				prev = cur;
				cur = cur->getNext();
				delete prev;
			}
			return;
		}
		
		~H_list(){
			clearSpace(m_head);
		}
};

void makeLog(ofstream& fout, string message){
	fout << message;
	cout << message;
}

int main(){
	H_list list;
	string str = "";
	string data = "(1(2(3(4(5(6(7))))3(45)))7)";
	list.makeList(data, 0, list.getHead(), 0);
	list.getPrintMessage(str, list.getHead());
	list.replaceAtom('7', '!', list.getHead());
	//cout << list.getHead().getData() << "\n";
	//cout << list.getCur().getData() << "\n";
	cout << str << "\n";
	str = "";
	list.getPrintMessage(str, list.getHead());
	cout << str << "\n";
	return 0;
}
