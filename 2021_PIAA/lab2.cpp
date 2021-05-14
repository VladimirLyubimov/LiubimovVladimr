#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <cmath>

using std::cout;
using std::cin;

void getGraph(int**& graph) {
    std::string st;
    while (1) {
        getline(cin, st);
        if (st.empty()) {
            break;
        }
        cout << st << '\n';

    }
    cout << 0 << '\n';
}

class Node {
private:
    char m_val;
    float m_path_val;
    float m_everistic_val;
    float m_total_val;
    std::vector<Node> m_neighbours;

public:
    Node(char val) :m_val(val) {
        m_path_val = 0;
        m_everistic_val = 0;
        m_total_val = 0;
    }

    void setPathVal(float value) {
        m_path_val = value;
    }

    char getValue() {
        return m_val;
    }

    void calcEveristic(Node target_node) {
        m_everistic_val = abs(static_cast<float>(static_cast<int>(m_val)) - static_cast<float>(static_cast<int>(target_node.getValue())));
    }

    void calcTotalValue() {
        m_total_val = m_path_val + m_everistic_val;
    }

    float getTotalValue() {
        return m_total_val;
    }

    void appendNeighbour(Node node) {
        m_neighbours.push_back(node);
    }

    bool isNeighbour(Node node) {
        for (int i = 0; i < m_neighbours.size(); i++) {
            if (m_neighbours[i].getValue() == node.getValue()) {
                return true;
            }
        }

        return false;
    }
};

class Graph {
public:
    std::vector<Node> m_data;

public:
    Graph(int** &Atable, int table_size) {
        for (int i = 0; i < table_size; i++) {
            char node_val = static_cast<char>(i + 97);
            m_data.push_back(Node(node_val))
        for (int i = 0; i < table_size; i++) {
            char node_val = static_cast<char>(i+97);
            for (int j = 0; j < table_size; i++) {
                if (Atable[i][j] >= 0) {
                    if(!isNodeExist)
                }
            }
        }
    };

    bool isNodeExist(char node_val) {
        for (int i = 0; i < m_data.size(); i++) {
            if (m_data[i].getValue() == node_val) {
                return true;
            }
        }

        return false;
    }
};

void Astar(int**& graph, int start, int finish) {
    std::vector<int> closed_set;
    std::queue<int> open_set;
    std::vector<int> path;

    open_set.push(start);
}

int main()
{
    int** graph = nullptr;
    cout << "Input data:\n";
    return 0;
}
