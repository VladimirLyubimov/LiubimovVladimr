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
		if(l.makeLoad(field) == 1)
			throw 1;	
	}
	
	catch(int){
		GameInit::EndGame(field);
		std::cerr << "Error in loading. File with name doen't exist or data is corrupted!\n";
		exit(0);
	}
}
