#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>

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
    char m_came_from;
    float m_path_val;
    float m_everistic_val;
    float m_total_val;

public:
    std::vector<Node> m_neighbours;

public:
    Node(char val = 0) :m_val(val) {
        m_came_from = 0;
        m_path_val = 0;
        m_everistic_val = 0;
        m_total_val = 0;
    }

    void setPathVal(float value) {
        m_path_val = value;
    }

    float getPathValue() {
        return m_path_val;
    }

    void setCameFrom(char value) {
        m_came_from = value;
    }

    char getCameFrom() {
        return m_came_from;
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

    friend bool operator== (const Node& node1, const Node& node2);
};

bool operator== (const Node& node1, const Node& node2) {
    return (node1.m_val == node2.m_val);
}

class Graph {
public:
    std::vector<Node> m_data;

public:
    Graph(int** &Atable, int table_size) {
        for (int i = 0; i < table_size; i++) {
            char node_val = static_cast<char>(i + 97);
            m_data.push_back(Node(node_val));
        }
        
        for (int i = 0; i < table_size; i++) {
            for (int j = 0; j < table_size; i++) {
                if (Atable[i][j] >= 0) {
                    m_data[i].appendNeighbour(m_data[j]);
                }
            }
        }
    }

    bool isNodeExist(char node_val) {
        for (int i = 0; i < m_data.size(); i++) {
            if (m_data[i].getValue() == node_val) {
                return true;
            }
        }

            return false;
        }
    };

bool cmp(Node node1, Node node2) {
    return (node1.getTotalValue() >= node2.getTotalValue());
}

    std::vector<char> Astar(Graph graph, int start, int finish, int**& Atable) {
        std::vector<Node> closed_set;
        std::vector<Node> open_set;
        std::vector<char> path;
        Node current_node;

        graph.m_data[start].calcEveristic(graph.m_data[finish]);
        graph.m_data[start].calcTotalValue();
        open_set.push_back(graph.m_data[start]);

        while (!open_set.empty()) {
            std::stable_sort(open_set.begin(), open_set.end(), cmp);
            current_node = open_set.back();

            if (current_node.getValue() == graph.m_data[finish].getValue()) {
                path.push_back(current_node.getValue());
                return path;
            }

            open_set.pop_back();
            closed_set.push_back(current_node);
            for (int i = 0; i < current_node.m_neighbours.size(); i++) {
                Node cur_neighbour = current_node.m_neighbours[i];
                if (std::find(closed_set.begin(), closed_set.end(), cur_neighbour) != closed_set.end()) {
                    continue;
                }

                float temporal_path_val = cur_neighbour.getPathValue() + Atable[static_cast<int>(current_node.getValue() - 97)][static_cast<int>(cur_neighbour.getValue() - 97)];
            }

        }
    }

    int main()
    {
        int** graph = nullptr;
        cout << "Input data:\n";
        return 0;
    }
