#pragma once
#include "../Logs/LogInterface.hpp"
#include "../Logs/FileLog.hpp"
#include "../Logs/ConsolLog.hpp"
#include "../Interface/MyInterface.hpp"
#include "PlayGroundStruct.hpp"
#include "SaveLoad.hpp"

class GameExecutor{
	public:
		static bool Play(PlayGround& field);
	private:
		static void MyClear(FileLog* Logfile, ConsolLog* consol, LogInterface* FLog, LogInterface* CLog);
};
