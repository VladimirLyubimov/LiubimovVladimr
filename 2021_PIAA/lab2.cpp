#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>

using std::cout;
using std::cin;

void getGraph(int**& graph) {
    char ch1, ch2;
    float val;
    while (cin >> ch1 >> ch2 >> val) {
        //cout << val << '\n';
        graph[static_cast<int>(ch1) - 97][static_cast<int>(ch2) - 97] = val;
        //cout << graph[static_cast<int>(ch1) - 97][static_cast<int>(ch2) - 97] << '\n';
    }
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
        m_path_val = 10000;
        m_everistic_val = 10000;
        m_total_val = 10000;
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
            for (int j = 0; j < table_size; j++) {
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
            //cout << current_node.getValue() << '\n';

            if (current_node.getValue() == graph.m_data[finish].getValue()) {
                path.push_back(current_node.getValue());
                return path;
            }
            
            cout << current_node.getValue() << ": ";
            for (int i = 0; i < open_set.size(); i++) {
                cout << open_set[i].getValue() << ' ';
            }
            cout << '\n';

            open_set.pop_back();
            closed_set.push_back(current_node);
            for (int i = 0; i < current_node.m_neighbours.size(); i++) {
                Node cur_neighbour = current_node.m_neighbours[i];
                //cout << cur_neighbour.getValue() << '\n';
                if (std::find(closed_set.begin(), closed_set.end(), cur_neighbour) != closed_set.end()) {
                    continue;
                }

                float temporal_path_val = current_node.getPathValue() + Atable[static_cast<int>(current_node.getValue() - 97)][static_cast<int>(cur_neighbour.getValue() - 97)];

                if (temporal_path_val < cur_neighbour.getPathValue()) {
                    cur_neighbour.setPathVal(temporal_path_val);
                    cur_neighbour.calcEveristic(graph.m_data[finish]);
                    cur_neighbour.calcTotalValue();
                }

                if (std::find(open_set.begin(), open_set.end(), cur_neighbour) == open_set.end()) {
                    open_set.push_back(cur_neighbour);
                }
                else {
                    open_set.erase(std::find(open_set.begin(), open_set.end(), cur_neighbour));
                    open_set.push_back(cur_neighbour);
                }
            }
        }

    }

    int main()
    {
        int size = 5;
        int** Atable = new int* [size];
        for (int i = 0; i < size; i++) {
            Atable[i] = new int[size];
        }
        
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                Atable[i][j] = -1;
            }
        }

        //cout << "Input data:\n";
        getGraph(Atable);
        
        /*for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                cout << Atable[i][j] << ' ';
            }
            cout << "\n";
        }*/

        Graph graph(Atable, size);
        std::vector<char> path = Astar(graph, 0, 4, Atable);
        for (int i = 0; i < path.size(); i++) {
            cout << path[i] << ' ';
        }
        cout << '\n';

        return 0;
    }
