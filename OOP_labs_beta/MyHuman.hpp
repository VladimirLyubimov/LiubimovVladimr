#pragma once
#include <cmath>

class MyHuman{
	public:
		int m_health;
		int m_damage;
		int m_x;
		int m_y;
		int m_level;
		int m_movepoints;
		int m_armor;
	protected:
		MyHuman(int x, int y, int health, int damage, int level, int movepoints, int armor);
	public:
		void Move(int dx, int dy);
		void takeDamage(int damage);
		int CalcDamage(int target_level, int target_armor, int target_health);
		void changeDamage(int ddamage);
		void changeLevel(int dlevel);
		void changeMovepoints(int dmovepoints);
		void changeArmor(int darmor);
		void getCoord(int &x, int &y);
		void setCoord(int x, int y);
		int getHealth();
		int getLevel();
		virtual char print() = 0;
		virtual void levelup();
};
