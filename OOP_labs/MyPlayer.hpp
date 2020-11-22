#pragma once
#include "MyHuman.hpp"

class MyPlayer : public MyHuman{
	private:
		int m_exp;
		bool m_collected;
		bool m_exit;
	public:
		MyPlayer(int x, int y, int health = 1000, int damage = 10, int level = 1, int movepoints = 5, int armor = 0, int exp = 0, bool collected = false);
		void addExp(int exp);
		void setCollected();
		bool getCoollected();
		void setExit();
		bool getExit();
		virtual void levelup();
		virtual char print();
};
