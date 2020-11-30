#pragma once
#include <cmath>

class MyHuman{
	protected:
		int m_health;
		int m_base_health;
		int m_damage;
		int m_x;
		int m_y;
		int m_level;
	protected:
		MyHuman(int x, int y, int health, int damage, int level);
	public:
		void Move(int dx, int dy);
		void takeDamage(int damage);
		int CalcDamage(int target_level, int target_health);
		void changeDamage(int ddamage);
		void changeLevel(int dlevel);
		void getCoord(int &x, int &y);
		void setCoord(int x, int y);
		int getHealth();
		int getLevel();
		virtual char print() = 0;
		virtual void levelup();
};
