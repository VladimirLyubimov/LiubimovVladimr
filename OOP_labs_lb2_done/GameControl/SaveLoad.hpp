#pragma once
#include "Save.hpp"
#include "Load.hpp"
#include "iostream"
#include "../GameControl/GameInit.hpp"
#include "../GameControl/PlayGroundStruct.hpp"
#include "../Interface/MyInterface.hpp"
#include <string>
#include <cstdlib>

using namespace std;

class SaveLoad{
	private:
		string m_Sfile;
		string m_Lfile;		
	private:
		void getLoadFileName();
		void getSaveFileName();		
	public:
		SaveLoad(): m_Sfile(""), m_Lfile(""){};
		~SaveLoad(){};
		void makeLoad(PlayGround& field);
		void makeSave(PlayGround& field);
		
};
