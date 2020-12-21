#pragma once
#include "PlayGroundStruct.hpp"
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

class Load{
	private:
		ifstream* m_file;
	private:
		bool checkMatrix(char** matrix, int x, int y);
		bool checkPlayer(int x, int y, int health, int damage, int lev, int exp, int collect, int width, int height);
	public:
		Load(const char* filename);
		~Load();
		int makeLoad(PlayGround& field);
};
