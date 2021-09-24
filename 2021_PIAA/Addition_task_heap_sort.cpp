#include <iostream>
#include <vector>

using std::cin;
using std::cout;

class MaxHeap{
private:
	std::vector<int> m_data;
	int m_size;
	int m_n = 2;

public:
	MaxHeap(std::vector<int> const & data, int n = 2) {
		for (int elem : data) {
			m_data.push_back(elem);
		}

		m_n = n;
		m_size = m_data.size();
	}

	int findMaxSon(int pos) {
		if (m_n * pos + 1 >= m_size) {
			return -1;
		}
		
		int res = m_n * pos + 1;
		for (int i = m_n * pos + 1; (i <= m_n * pos + m_n) && (i < m_size); i++) {
			if (m_data[res] < m_data[i]) {
				res = i;
			}
		}
		
		return res;
	}

	void siftDown(int pos) {
		int max_son = findMaxSon(pos);;
		while (max_son != -1) {
			if (m_data[max_son] > m_data[pos]) {
				int temp = m_data[max_son];
				m_data[max_son] = m_data[pos];
				m_data[pos] = temp;
				pos = max_son;
			}
			else {
				break;
			}

			max_son = findMaxSon(pos);
		}
	}

	void dragMax() {
		int temp = m_data[m_size - 1];
		m_data[m_size - 1] = m_data[0];
		m_data[0] = temp;
		m_size -= 1;
	}

	void buildHeap() {
		int i = m_size / m_n;
		while (i >= 0) {
			siftDown(i);
			i -= 1;
		}
	}

	int getSize() {
		return m_size;
	}

	void getSorted(std::vector<int>& data) {
		data.clear();
		for (int i = m_size; i < m_data.size(); i++) {
			data.push_back(m_data[i]);
		}
	}

	void printHeap() {
		cout << "Heap: ";
		for (int i = 0; i < m_size; i++) {
			cout << m_data[i] << ' ';
		}
		cout << "\nSorted: ";
		for (int i = m_size; i < m_data.size(); i++) {
			cout << m_data[i] << ' ';
		}

		cout << "\n\n";
	}
};


void heapSort(MaxHeap& heap) {
	while (heap.getSize() > 0) {
		heap.dragMax();
		heap.siftDown(0);
		heap.printHeap();
	}
}

int main()
{
	std::vector<int> data;
	int size;
	cout << "Input size of array:\n";
	cin >> size;
	cout << "Input array elements:\n";
	for (int i = 0; i < size; i++) {
		int a;
		cin >> a;
		data.push_back(a);
	}

	MaxHeap heap(data);
	heap.buildHeap();;
	heap.printHeap();
	heapSort(heap);
	heap.getSorted(data);
	cout << "Result:\n";
	for (int elem : data) {
		cout << elem << ' ';
	}

	cout << '\n';
	return 0;
}
