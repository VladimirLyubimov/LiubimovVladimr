#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

void writeLog(int step, ofstream& fout, string message){//логирование промежуточных и итоговых данных
	for(int i = 0; i < step; i++){
		fout << "\t";
		cout << "\t";
	}
	fout << message;
	cout << message;
}

template <class T>
int getData(T* &arr, ifstream& fin){
	int size = 0;
	int mem_size = 0;

	while(1){
		if(size == mem_size){
			mem_size += 10;
			T* new_arr = new T[mem_size];
			for(int i = 0; i < size; i++){
				new_arr[i] = arr[i];
			}
			delete[] arr;
			arr = new_arr;
		}

		if(fin.eof()){
			return size;
		}

		fin >> arr[size];
		size += 1;
	}

	return size;
}

template <class T>
void Sort(T* &arr, int size, ofstream& fout){
	int cur = 0;
	int j = 0;
	for(int i = 0; i < size; i++){
		cur = arr[i];
		j = i-1;

		cout << "Sorted part of array: ";
		for(int k = 0; k <= j; k++){
			cout << "\033[32m" << arr[k] << ' ';
		}
		cout << "\033[0mCurent elemrnt is " << "\033[33m" << cur << ' ';
		cout << "\033[0mUnsorted part of array: ";
		for(int k = i+1; k < size; k++){
			cout << "\033[36m" << arr[k] << ' ';
		}
		cout << "\033[0m\n";
		cout << "Current index is " << i << '\n';

		while(arr[j] > cur && j >= 0){
			cout << "\033[32m" << arr[j] << "\033[0m at positon " << j << " is more than \033[33m" << cur << "\033[0m\n";
			arr[j+1] = arr[j];
			j -= 1;
		}
		if(j >= 0){
			cout << "\033[32m" << arr[j] << "\033[0m at positon " << j << " is less or equal than \033[33m" << cur << "\033[0m. Element insert into position with index " << j+1 << '\n';
		}
		else{
			cout << "Start of array nave been reached. " << cur << " is insert into the start of array.\n";
		}
		arr[j+1] = cur;
	}
}

int main(){
	int* arr = nullptr;
	ifstream fin("./test.txt");
	int size = getData(arr, fin);
	ofstream fout("./res.txt");
	fin.close();

	for(int i = 0; i < size; i++){
		cout << arr[i] << ' ';
	}
	cout << '\n';

	Sort(arr, size, fout);

	for(int i = 0; i < size; i++){
		cout << arr[i] << ' ';
	}
	cout << '\n';

	fout.close();

	return 0;
}
