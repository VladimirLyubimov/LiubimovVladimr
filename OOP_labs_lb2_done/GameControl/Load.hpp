#pragma once
#include "PlayGroundStruct.hpp"
#include <fstream>
#include <iostream>

using namespace std;

class Load{
	private:
		ifstream* m_file;
	public:
		Load(const char* filename);
		~Load();
		int makeLoad(PlayGround& field);
};
