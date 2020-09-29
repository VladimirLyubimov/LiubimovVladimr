#pragma once
#include "MyMaze.hpp"
#include "MyCell.hpp"

class MyPlayer{
	private:
		int m_x;
		int m_y;
		int m_health;
		int m_movepoints;
		int m_damage;
		int m_experience;
		int m_level;
	public:
		MyPlayer(int x, int y, int health, int movepoints, int damage, int exp, int level);
		MyPlayer(const MyPlayer &obj);
		void Move(int dx, int dy);//перемешение игрока
		void setHealth(int health);//изменение здоровья
		void getCoordinates(int &x, int &y);//получение координат игрок
};
