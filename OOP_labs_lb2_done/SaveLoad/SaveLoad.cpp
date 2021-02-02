#include "SaveLoad.hpp"

void SaveLoad::getSaveFileName(){
	m_Sfile = MyInterface::getFilename();
}

void SaveLoad::getLoadFileName(){
	m_Lfile = MyInterface::getFilename();
}

void SaveLoad::makeSave(PlayGround& field){
	getSaveFileName();
	Save s(m_Sfile.data());
	try{
		if(s.makeSave(field) == 1)
			throw 1;
	}
	
	catch(int){
		remove(s.getFilename());
		std::cerr << "Error in saving. Saving canceled!\n";
	}
}

void SaveLoad::makeLoad(PlayGround& field){
	getLoadFileName();
	Load l(m_Lfile.data());
	try{
		int a = l.makeLoad(field);
		if(a)
			throw a;	
	}
	
	catch(int err){
		GameInit::EndGame(field);
		switch (err){
			case 1:
				std::cerr << "Error in loading. File with name doesn't exist or corrupted!\n";
				break;
			case 2:
				std::cerr << "Error in loading. Maze data corrupted!\n";
				break;
			case 3:
				std::cerr << "Error in loading. Player data corrupted!\n";
				break;
			case 4:
				std::cerr << "Error in loading. Enemies data corrupted!\n";
				break;
		}
		exit(0);
	}
}
