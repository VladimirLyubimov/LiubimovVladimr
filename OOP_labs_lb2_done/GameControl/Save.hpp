#pragma once
#include "PlayGroundStruct.hpp"
#include <fstream>
#include <iostream>

using namespace std;

class Save{
	private:
		ofstream* m_file;
	public:
		Save(const char* filename);
		~Save();
		int makeSave(PlayGround& field);
};
