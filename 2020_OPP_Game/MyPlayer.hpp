#pragma once
#include "MyHuman.hpp"

class MyPlayer : public MyHuman{
	private:
		int m_exp;
	public:
		MyPlayer(int x, int y, int health = 1000, int damage = 10, int level = 1, int movepoints = 5, int armor = 0, int exp = 0);
		void addExp(int exp);
		virtual void levelup();
		virtual char print();		
};
