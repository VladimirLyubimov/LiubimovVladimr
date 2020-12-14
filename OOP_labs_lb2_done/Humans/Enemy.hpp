#pragma once
#include "MyHuman.hpp"
#include "MyMaze.hpp"

#template <class T>

class Enemy: public MyHuman{
	private:
		T* behavior;
		
};
