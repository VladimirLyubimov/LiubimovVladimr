#pragma once
#include "PlayGroundStruct.hpp"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Save{
	private:
		ofstream* m_file;
		std::string* m_fname;
	public:
		Save(const char* filename);
		~Save();
		int makeSave(PlayGround& field);
		const char* getFilename();
};
