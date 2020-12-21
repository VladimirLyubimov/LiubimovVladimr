#pragma once
#include "../Maze/MyMaze.hpp"
#include "../ActiveObjects/MyDynamite.hpp"
#include "../ActiveObjects/MyExit.hpp"
#include "../ActiveObjects/MyBonus.hpp"
#include "../ActiveObjects/MyAim.hpp"
#include "../Humans/PlayerControl.hpp"
#include "../Humans/Enemy.hpp"
#include "../Humans/Behaviors/Behavior.hpp"
#include "../Humans/Behaviors/BAttack.hpp"
#include "../Humans/Behaviors/BDamage.hpp"
#include "../Humans/Behaviors/BLevel.hpp"

struct PlayGround{
	MyMaze* m_maze = nullptr;
	MyObject* m_finish = nullptr;
	MyObject* m_bonus = nullptr;
	MyObject* m_aim = nullptr;
	MyObject* m_dynamite = nullptr;
	PlayerControl* m_hero = nullptr;
	SuperEnemy** m_enemies = nullptr;
	int enemy_amount = 0;
};
