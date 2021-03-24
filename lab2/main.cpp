#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

class Node{//класс реализующий атом
	private:
		char m_data;//значение атома
		Node* m_next;//указательна следующий за ним на том же уровне атом 
		Node* m_child;//указатель на "ребёнка" этого атома, расположеного на уровень ниже
	public:
		Node(char data = 0, Node* next = nullptr, Node* child = nullptr): m_data(data), m_next(next), m_child(child){
		}//конструктор; инициализирует значение атома 0, а указатели - nullptr
		
		~Node(){}
		
		void setNext(Node* next){//устанвливает следющеий за этим атомом на том же уровне атом
			m_next = next;
		}
		
		void setChild(Node* child){//устанавливает "ребёнка"
			m_child = child;
		}
		
		void setData(char data){//устанавливает значение атома
			m_data = data;
		}
		
		Node* getNext(){//возвращает указатель на следующий атом
			return m_next;
		}
	
		Node* getChild(){//возвращает указатель на ребёнка
			return m_child;
		}
		
		char getData(){//возвращает значение атома
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
	if(c_data == ' '){
		c_data = '|';
	}
	message += c_data;
	message += end;
}

class H_list{//класс, реализующий иерархический список
	private:
		Node* m_head;//голова списка
	public:
		H_list(){//конструктор
			m_head = nullptr;
		}
				
		void printList(string& str, Node* cur){//рекурсивно создаёт сокращённую скобочную запись списка
			str += "(";
			char atom;
			while(cur){
				atom = cur->getData();
				if(atom == 0 || atom == ' '){
					atom = '|';
				}
				str += atom;
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
			if(data == "" || data == "()"){
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
					makeLogMessage(log_message, "The first element created. Its value is ", data[0], "\n");
					writeLog(level, fout, log_message);
					log_message = "";
					continue;
				}
				
				if(data[i] == '(' && !m_head){
					i += 1;
					m_head = new Node(data[i]);
					cur = m_head;
					makeLogMessage(log_message, "The first element created. Its value is ", data[i], "\n");
					writeLog(level, fout, log_message);
					i += 1;
					log_message = "";
					continue;
				}

				if(data[i] == '(' && data[i-1] == ')'){
					makeLogMessage(log_message, "The one more element created. Its value is ", '|', "\n");
					writeLog(level, fout, log_message);
					cur->setNext(new Node('|'));
					cur = cur->getNext();
					log_message = "";
					if(data[i] != '('){
						i += 1;
						continue;
					}
				}

				if(data[i] == '(' && data[i+1] == '('){
					cur->setChild(new Node('|'));
					i += 1;
					makeLogMessage(log_message, "The building of new level of hierarchical list have been started. Recursion used. The one more element created. Its value is ", '|', "\n");
					writeLog(level+1, fout, log_message);
					i = makeList(data, i, cur->getChild(), level+1, fout);
					log_message = "";
					continue;
				}

				if(data[i] == '(' && data[i+1] == ')'){
					cur->setChild(new Node('|'));
					i += 1;
					makeLogMessage(log_message, "The building of new level of hierarchical list have been started. Recursion used. The one more element created. Its value is ", '|', "\n");
					writeLog(level+1, fout, log_message);
					i = makeList(data, i, cur->getChild(), level+1, fout);
					log_message = "";
					continue;
				}

				if(data[i] == '('){
					i += 1;
					cur->setChild(new Node(data[i]));
					i += 1;
					makeLogMessage(log_message, "The building of new level of hierarchical list have been started. Recursion used. The one more element created. Its value is ", data[i-1], "\n");
					writeLog(level+1, fout, log_message);
					i = makeList(data, i, cur->getChild(), level+1, fout);
					log_message = "";
					continue;
				}

				if(data[i] == ')'){
					i += 1;
					writeLog(level, fout, "Return to previos level of the list.\n");
					return i;
				}
				
				if(data[i] != ')' && data[i] != '('){
					makeLogMessage(log_message, "The one more element created. Its value is ", data[i], "\n");
					writeLog(level, fout, log_message);
					cur->setNext(new Node(data[i]));
					cur = cur->getNext();
					i += 1;
					log_message = "";
					continue;
				}
				log_message = "";
			}
			
			return 0;
		}
		
		void replaceAtom(char atom, char change, Node* cur,  ofstream& fout, int level){
			string log_message;
			while(cur){
				log_message = "";
				makeLogMessage(log_message, "The atom with value ", atom, " should be replaced. ");
				writeLog(level, fout, log_message);
				log_message = "";
				makeLogMessage(log_message, "The value of current atom is ", cur->getData(), ". ");
				writeLog(0, fout, log_message);

				if(cur->getData() == atom){
					log_message = "";
					makeLogMessage(log_message, "So this atom should be replacement. It will be replaced with ", change, "");
					writeLog(0, fout, log_message);
					cur->setData(change);
				}
				else{
					log_message = "";
					makeLogMessage(log_message, "So this atom should not be replacement", 0, ".");
					writeLog(0, fout, log_message);
				}
				
				writeLog(0, fout, "\n");

				if(cur->getChild()){
					replaceAtom(atom, change, cur->getChild(), fout, level+1);
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
	cout << "Input the path to data file:\n";
	string fname;
	cin >> fname;
	ifstream fin(fname);
	if(!fin.is_open()){
		cout << "Opening file with test data failed!\n";
		return 0;
	}
	cout << "Input the path to result file:\n";
	cin >> fname;
	ofstream fout(fname);
	if(!fout.is_open()){
		cout << "Opening file for writing result data failed!\n";
		return 0;
	}

	char atom_f, atom_r;
	string data;
	cout << "Input atoms for replacement (target replacement):\n";
	cin >> atom_f >> atom_r;
	getline(fin, data);
	writeLog(0, fout, "\nThe source data is:\n" + data + "\n");

	H_list list;
	string out_data = "";
	list.makeList(data, 0, list.getHead(), 0, fout);
	list.printList(out_data, list.getHead());
	writeLog(0, fout, "\nThe source list is:\n" + out_data + "\n\n");
	list.replaceAtom(atom_f, atom_r, list.getHead(), fout, 0);
	out_data = "";
	list.printList(out_data, list.getHead());
	writeLog(0, fout, "\nThe list with replacements is:\n" + out_data + "\n");

	fin.close();
	fout.close();
	return 0;
}
