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

void writeLog(int step, ofstream& fout, string message){//логирование промежуточных и итоговых данных
	for(int i = 0; i < step; i++){
		fout << "\t";
		cout << "\t";
	}
	fout << message;
	cout << message;
}

void makeLogMessage(string& message, const char* st_data, char c_data){
	message += st_data;
	message += c_data;
	message += "\n";
}

class H_list{
	private:
		Node* m_head;
	public:
		H_list(){
			m_head = nullptr;
		}
				
		void printList(string& str, Node* cur){
			str += "(";
			while(cur){
				str += cur->getData();
				if(cur->getChild()){
					printList(str, cur->getChild());
				}
				cur = cur->getNext();
			}
			str += ")";
		}
				
		Node* getHead(){
			return m_head;
		}
				
		int makeList(string& data, int i, Node* cur, int level,  ofstream& fout){
			if(data == ""){
				m_head = new Node(0);
				writeLog(level, fout, "The empty hierarchical created.\n");
				return 0;
			}
			
			string log_message = "";
			while(i < data.size()){
				if(data[0] != '(' && !m_head){
					m_head = new Node(data[0]);
					cur = m_head;
					i += 1;
					makeLogMessage(log_message, "The first element created. Its value is ", data[0]);
					writeLog(level, fout, log_message);
					continue;
				}
				
				if(data[i] == '(' && !m_head){
					i += 1;
					m_head = new Node(data[i]);
					cur = m_head;
					makeLogMessage(log_message, "The first element created. Its value is ", data[i]);
					writeLog(level, fout, log_message);
					i += 1;
					continue;
				}
				
				if(data[i] == '(' && m_head){
					i += 1;
					cur->setChild(new Node(data[i]));
					i += 1;
					makeLogMessage(log_message, "The building of new level of hierarchical list have been started. Recursion used. The one more element created. Its value is ", data[i-1]);
					writeLog(level, fout, log_message);
					i = makeList(data, i, cur->getChild(), level+1, fout);
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
					makeLogMessage(log_message, "The one more element created. Its value is ", data[i]);
					writeLog(level, fout, log_message);
					cur->setNext(new Node(data[i]));
					cur = cur->getNext();
					i += 1;
					continue;
				}
				log_message = "";
			}
			
			return 0;
		}
		
		void replaceAtom(char atom, char change, Node* cur,  ofstream& fout){
			while(cur){
				if(cur->getChild()){
					replaceAtom(atom, change, cur->getChild(), fout);
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

int main(){
	H_list list;
	ofstream fout;
	fout.open("./res.txt");
	string str = "";
	string data = "(1(2(3(4(5(6(7))))3(45)))7)";
	list.makeList(data, 0, list.getHead(), 0, fout);
	list.printList(str, list.getHead());
	list.replaceAtom('7', '!', list.getHead(), fout);
	//cout << list.getHead().getData() << "\n";
	//cout << list.getCur().getData() << "\n";
	cout << str << "\n";
	str = "";
	list.printList(str, list.getHead());
	cout << str << "\n";
	fout.close();
	return 0;
}
