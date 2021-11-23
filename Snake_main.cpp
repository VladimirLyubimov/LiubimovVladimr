#include <iostream>

using namespace std;

typedef struct MyCoord{
	int x;
	int y;
} coord;

class Section{
	private:
		coord m_position;
		Section* m_next;
		Section* m_prev;
	
	public:
		Section(coord pos){
			m_position = pos;
			m_next = nullptr;
			m_prev = nullptr;
		}
		
		coord getPos(){
			return m_position;
		}
		
		void setPos(coord pos){
			m_position = pos;
		}
		
		Section* getPrev(){
			return m_prev;
		}
		
		Section* getNext(){
			return m_next;
		}
		
		void addSection(coord pos){
			m_next = new Section(pos);
			this->m_next->m_prev = this;
		}
		
		~Section(){
			if(this->m_next){
				delete m_next;
			}
			
			cout << "Delete section with coordinats " << m_position.x << ',' << m_position.y << '\n';
		}
};

class Snake{
	private:
		int m_size;
		Section* m_head;
		Section* m_tail;
	public:
		Snake(coord pos){
			m_size = 1;
			m_head = new Section(pos);
			m_tail = m_head;
		}
		
		void addSection(coord pos){
			m_tail->addSection(pos);
			m_tail = m_tail->getNext();
		}
		
		~Snake(){
			if(this->m_head){
				delete m_head;
			}
			
			cout << "Delete head!\n";
		}
};

int main(){
	Snake* Petya = new Snake({0, 0});
	for(int i = 1; i < 10; i++){
		Petya->addSection({i, 0});
	}
	
	delete Petya;
	return 0;
}
