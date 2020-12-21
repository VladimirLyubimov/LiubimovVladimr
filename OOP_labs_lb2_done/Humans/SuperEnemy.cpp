
#include "SuperEnemy.hpp"

std::string SuperEnemy::getLogData(){
	if(this->m_alive){
		std::string data("Enemy position is (");
		int x = 0;
		int y = 0;
		this->getCoord(x,y);
		data += std::to_string(x) + ";" + std::to_string(y) + "). ";
		data += "Health = " + std::to_string(this->getHealth()) + ". ";
		data += "Level = " + std::to_string(this->getLevel()) + ". ";
		data += "Damage = " + std::to_string(this->getDamage()) + ".";
		
		if(this->m_inter){
			data += " Interaction has been completed!";
			m_inter = false;
		}
		if(this->m_kill){
			data += " Target has been destroyed!";
			m_kill = false;
		}
		if(this->getHealth() <= 0)
			data += " Health isn't below 0. Died!";
		data += "\n";
		return data;
	}
	
	return "";
}

void SuperEnemy::MakeLog(LogInterface* FLog, LogInterface* CLog, SuperEnemy* LogObj){
	if(FLog)
		*FLog << LogObj;
	if(CLog)
		*CLog << LogObj;
}

LogInterface& operator <<(LogInterface& log, SuperEnemy* Obj){
	log.writeLog(Obj->getLogData());
	return log;
}
