#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using std::cin;
using std::cout;

class Square {
public:
    int m_x;
    int m_y;
    int m_size;
    bool m_is_root;
public:
    Square(int x = 0, int y = 0, int size = 0, bool root = false) : m_x(x), m_y(y), m_size(size), m_is_root(root) {}
    Square(const Square& square) {
        m_x = square.m_x;
        m_y = square.m_y;
        m_size = square.m_size;
        m_is_root = square.m_is_root;
    }
};

class Table {
private:
    std::vector<Square> m_cur_state = {};
    std::vector<Square> m_best_state = {};
    std::vector<Square> m_avaliable = {};
    int** m_matrix;
    int m_size;
    int m_count;
    int m_min_count = 1000;
    bool m_is_end = false;

public:
    Table(int size = 2) : m_size(size) {
        m_matrix = new int* [m_size];
        for (int i = 0; i < m_size; i++) {
            m_matrix[i] = new int[m_size];
            for (int j = 0; j < m_size; j++) {
                m_matrix[i][j] = 0;
            }
        }
        m_count = 0;
        m_min_count = size * size;
    }

    void setRootSquares(std::vector<int> const& squares) {
        for (auto elem : squares) {
            m_avaliable.emplace_back(0, 0, elem, true);
        }
    }

    void updateCoord(Square& elem) {
        if (elem.m_x + 1 < m_size) {
            elem.m_x += 1;
        }
        else {
            elem.m_y += 1;
            elem.m_x = 0;
        }
    }

    bool putRootSquare() {
        Square square = m_avaliable.front();
        while (1) {
            if (square.m_y >= m_size) {
                return false;
            }
            if (checkPlace(square.m_x, square.m_y, square.m_size)) {
                putSquare(square.m_x, square.m_y, square.m_size, true);
                m_avaliable.erase(m_avaliable.begin());
                return true;
            }
            else {
                updateCoord(square);
            }
        }
    }

    void deleteRootSquare(){
        Square square = m_cur_state.back();
        if (!m_avaliable.empty()) {
            m_avaliable.front().m_x = 0;
            m_avaliable.front().m_y = 0;
        }
        deleteSquare(square);
        updateCoord(square);
        m_avaliable.emplace(m_avaliable.begin(), square.m_x, square.m_y, square.m_size, true);
        m_cur_state.pop_back();
    }

    bool placeRootSquares() {
        while (!m_avaliable.empty()) {
            //cout << "!!!\n";
            if (!putRootSquare()) {
                if (!m_cur_state.empty()) {
                    //cout << "!\n";
                    deleteRootSquare();
                    //cout << m_cur_state.size() << ' ' << m_avaliable.size() << '\n';
                }
                else {
                    return false;
                }
            }
        }

        return true;
    }

    bool checkPlace(int x, int y, int square_size) {
        if (y + square_size > m_size || x + square_size > m_size) {
            return false;
        }
        for (int i = y; i < y + square_size; i++) {
            for (int j = x; j < x + square_size; j++) {
                if (m_matrix[i][j] != 0) {
                    return false;
                }
            }
        }

        return true;
    }

    void putSquare(int x, int y, int square_size, bool root = false) {
        m_cur_state.emplace_back(x, y, square_size, root);
        for (int i = y; i < y + square_size; i++) {
            for (int j = x; j < x + square_size; j++) {
                m_matrix[i][j] = m_count + 1;
            }
        }
        m_count += 1;
    }

    bool prepareTable() {
        bool res = placeRootSquares();
        if (res) {
            fillTable();
            m_min_count = m_count;
        }

        return res;
    }

    void deleteSquare(Square const& square) {
        for (int i = square.m_y; i < square.m_y + square.m_size; i++) {
            for (int j = square.m_x; j < square.m_x + square.m_size; j++) {
                m_matrix[i][j] = 0;
            }
        }
        m_count -= 1;
    }

    std::pair<int, int> findPlace() {
        for (int i = 0; i < m_size; i++) {
            for (int j = 0; j < m_size; j++) {
                if (m_matrix[i][j] == 0) {
                    return std::make_pair(j, i);
                }
            }
        }
        return std::make_pair(-1, -1);
    }

    void setSquare(int x, int y) {
        int size = 1;
        while (checkPlace(x, y, size)) {
            size += 1;
        }
        size -= 1;
        putSquare(x, y, size, false);
    }

    void fillTable() {
        std::pair<int, int> place = findPlace();
        while (place.first != -1 && m_count <= m_min_count) {
            setSquare(place.first, place.second);
            place = findPlace();
        }
    }

    bool isFull() {
        return findPlace().first == -1;
    }

    void checkSplit() {
        if (m_count <= m_min_count) {
            m_best_state = m_cur_state;
            m_min_count = m_count;
        }
    }

    void stepBack() {
        while (1) {
            Square last = m_cur_state.back();
            if (last.m_is_root) {
                m_is_end = true;
                break;
            }
            int last_size = last.m_size;
            if (last_size == 1) {
                deleteSquare(last);
                m_cur_state.pop_back();
                continue;
            }
            else {
                deleteSquare(last);
                int last_x = last.m_x;
                int last_y = last.m_y;
                m_cur_state.pop_back();
                putSquare(last_x, last_y, last_size - 1, false);
                fillTable();
                break;
            }
        }

    }

    void makeSplit() {
        while (1) {
            cout << "Cur split:\n";
            for (auto& square : m_cur_state) {               
                cout << square.m_x + 1 << ' ' << square.m_y + 1 << ' ' << square.m_size << ' ' <<  square.m_is_root <<'\n';
            }
            cout << "\n\n";
            stepBack();
            if (m_is_end) {
                if (isFull()) {
                    checkSplit();
                }

                deleteRootSquare();
                bool res = placeRootSquares();
                if (!res) {
                    cout << "End\n";
                    break;
                }
                fillTable();
                
                if (isFull()) {
                    checkSplit();
                }
                m_is_end = false;
                continue;
            }
            if (isFull()) {
                checkSplit();
            }
        }
    }

    std::vector<Square> getSplit() {
        if (prepareTable()) {
            makeSplit();
        }
        return m_best_state;
    }

    void addSquareToPicture(int x, int y, int square_size, int number) {
        for (int i = y; i < y + square_size; i++) {
            for (int j = x; j < x + square_size; j++) {
                m_matrix[i][j] = number + 1;
            }
        }
    }

    void makeSplitPicture() {
        for (int i = 0; i < m_min_count; i++) {
            Square elem = m_best_state[i];
            addSquareToPicture(elem.m_x, elem.m_y, elem.m_size, i);
        }
    }

    void drawSplit() {
        makeSplitPicture();
        for (int i = 0; i < m_size; i++) {
            for (int j = 0; j < m_size; j++) {
                cout << m_matrix[i][j];
            }
            cout << '\n';
        }
    }

    ~Table() {
        for (int i = 0; i < m_size; i++) {
            delete[] m_matrix[i];
        }

        delete[] m_matrix;
    }
};

void printAnswer(std::vector<Square> const& result) {
    if (result.empty()) {
        cout << "No split for this data!";
    }
    else {
        cout << result.size() << '\n';
        for (Square const& square : result) {
            cout << square.m_x + 1 << ' ' << square.m_y + 1 << ' ' << square.m_size << '\n';
        }
    }
}

int main()
{
    int table_size, list_size;
    std::vector<int> lengths;
    cout << "Input size of table and amount of given squares:\n";
    cin >> table_size >> list_size;
    cout << "Input length of the given squares divided by space:\n";
    for (int i = 0; i < list_size; i++) {
        int a;
        cin >> a;
        lengths.push_back(a);
    }
    std::sort(lengths.begin(), lengths.end());
    Table table(table_size);
    table.setRootSquares(lengths);
    printAnswer(table.getSplit());
    //table.drawSplit();
    return 0;
}
