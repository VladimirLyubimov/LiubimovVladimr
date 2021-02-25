#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

int SecondOrderDet(int** matrix){
	return matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];
}

int** MakeMinor(int** matrix, int line, int size){
	int** minor = new int*[size-1];
	for(int i = 0; i < size-1; i++){
		minor[i] = new int[size-1];
	}
	
	int i = 0;
	int k = 0;
	while(k < size){
		if(k != line){
			for(int j = 0; j < size-1; j++){
				minor[i][j] = matrix[k][j+1];
			}
			k++;
			i++;
		}
		else{
			k++;
		}
	}
	return minor;
}

void WriteLog(int step, ofstream& fout, string message){
	for(int i = 0; i < step; i++)
		fout << "\t";
	fout << message;
}

int CalcMinor(int** matrix, int size, int step, ofstream& fout){
	int res = 0;
	if(size == 1){
		WriteLog(step, fout, "It's is the simplest matrix content only one element.\n");
		return matrix[0][0];
	}
	
	if(size == 2){
		WriteLog(step, fout, "The 2x2 matrix have been found. Determinant can be found without recursion.\n");
		return SecondOrderDet(matrix);
	}
	
	for(int i = 0; i < size; i++){
		int** minor = MakeMinor(matrix, i, size);
		WriteLog(step, fout, "To find this " + to_string(size) + "x" + to_string(size) + " matrix determinant the additional minor of elemet " + to_string(i+1) + ";1 should be found.\n");
		int minor_value = CalcMinor(minor, size-1, step + 1, fout);
		res += (pow(-1, i+2) * matrix[i][0] * minor_value);
		WriteLog(step, fout, "The value of this minor is " + to_string(minor_value) + ". Current value of determinant of full matrix for this minor is " + to_string(res) + ".\n");
		for(int j = 0; j < size-1; j++){
			delete[] minor[j];
		}
		delete[] minor;
	}
	
	return res;
}

int main(){
	cout << "Input the path to data file:\n";
	string fname;
	//cin >> fname;
	ifstream fin("./test.txt");
	cout << "Input the path to result file:\n";
	//cin >> fname;
	ofstream fout("./res.txt");
	
	int size;
	fin >> size;
	int** matrix = new int*[size];
	for(int i = 0; i < size; i++){
		matrix[i] = new int[size];
	}
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			fin >> matrix[i][j];
		}
	}
	
	int det = CalcMinor(matrix, size, 0, fout);
	fout << det << "\n";
	
	for(int j = 0; j < size-1; j++){
			delete[] matrix[j];
		}
		delete[] matrix;

	return 0;
}
