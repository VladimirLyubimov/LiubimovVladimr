#include "iostream"

#define _USE_MATH_DEFINES
#include "cmath"

double ValueCalculation(double x, double y, double z){//вычисляет значение функции в заданной точке
	double res1, res2, res3, res;
	res1 = z + pow(z, 2.0)/(2.0*y);
	res2 = pow(((x + 0.5)/5.0), 2.0);
	res3 = 3/y;
	res = M_PI * (res1 + res2) - res3;
	return res;
}

void CycleWhile(double x, double y, double z){
	std::cout << "while() cycle:\n";
	while (x <= 3.0){
		std::cout << "Value of F(" << x << ") = " << ValueCalculation(x,y,z) << "\n";
		x += 0.3;
	}
}

void CycleDoWhile(double x, double y, double z){
	std::cout << "\n";
	std::cout << "do...while() cycle:\n";
	do{
		std::cout << "Value of F(" << x << ") = " << ValueCalculation(x,y,z) << "\n";
		x += 0.3;
	}while (x <= 3.0);
}

void CycleFor(double x, double y, double z){
	std::cout << "\n";
	std::cout << "for() cycle:\n";
	for(x; x <= 3.0; x += 0.3){
		std::cout << "Value of F(" << x << ") = " << ValueCalculation(x,y,z) << "\n";
	}
}

int main(){
	double x = -1.1;
	double y = 1.88;
	double z = 0.2;
	CycleWhile(x,y,z);
	CycleDoWhile(x,y,z);
	CycleFor(x,y,z);
	return 0;
}
