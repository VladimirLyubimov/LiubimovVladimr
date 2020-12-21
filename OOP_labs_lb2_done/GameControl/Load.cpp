#include "Load.hpp"

Load::Load(const char* filename){
	m_file = new ifstream(filename, fstream::in);
}

Load::~Load(){
	if(m_file->is_open())
		m_file->close();
	delete m_file;
}

int Load::makeLoad(PlayGround& field){
	if(!m_file->is_open())
		return 1;
		
	//read maze
	int height, width;
	*m_file >> width >> height;
	cout << width << " " << height;
}
