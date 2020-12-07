#pragma once
#include "../Logs/LogInterface.hpp"
#include "../Logs/FileLog.hpp"
#include "../Logs/ConsolLog.hpp"
#include "../Interface/MyInterface.hpp"
#include "PlayGroundStruct.hpp"

class GameExecutor{
	public:
		static void Play(PlayGround& field);
};
