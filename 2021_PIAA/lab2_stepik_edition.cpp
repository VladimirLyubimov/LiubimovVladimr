#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>

using std::cout;
using std::cin;

void increaseSize(int**& Atable, int new_length, int old_length) {
    int** new_table = new int* [new_length];
    for (int i = 0; i < new_length; i++) {
        new_table[i] = new int[new_length];
    }

    if (old_length != 0) {
        for (int i = 0; i < new_length; i++) {
            for (int j = 0; j < new_length; j++) {
                if (i < old_length && j < old_length) {
                    new_table[i][j] = Atable[i][j];
                }
                else {
                    new_table[i][j] = -1;
                }
            }
        }
    }
    else {
        for (int i = 0; i < new_length; i++) {
            for (int j = 0; j < new_length; j++) {
                new_table[i][j] = -1;
            }
        }
    }

    Atable = new_table;
}

class Node {
private:
    char m_val;
    int m_index;
    int m_came_from;
    float m_path_val;
    float m_everistic_val;
    float m_total_val;

public:
    std::vector<int> m_neighbours;

public:
    Node(char val = 0) :m_val(val) {
        m_came_from = -1;
        m_index = -1;
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

    void setCameFrom(int value) {
        m_came_from = value;
    }

    int getCameFrom() {
        return m_came_from;
    }

    void setIndex(int value) {
        m_index = value;
    }

    int getIndex() {
        return m_index;
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

    void appendNeighbour(int node) {
        m_neighbours.push_back(node);
    }
};

class Graph {
public:
    std::vector<Node> m_data;

public:
    Graph(int**& Atable) {
        int size = 0;
        int max = size;
        char node1, node2;
        float val;
        std::vector<char> nodes;
        while (cin >> node1 >> node2 >> val) {
            if (std::find(nodes.begin(), nodes.end(), node1) == nodes.end() && std::find(nodes.begin(), nodes.end(), node2) == nodes.end()) {
                max += 2;
                nodes.push_back(node1);
                nodes.push_back(node2);
                m_data.push_back(Node(node1));
                m_data[size].setIndex(size);
                m_data.push_back(Node(node2));
                m_data[size+1].setIndex(size+1);
                m_data[size].appendNeighbour(size+1);

                increaseSize(Atable, max, size);
                Atable[size][size + 1] = val;
                size = max;
                continue;
            }

            if (std::find(nodes.begin(), nodes.end(), node1) != nodes.end() && std::find(nodes.begin(), nodes.end(), node2) == nodes.end()) {
                max += 1;
                nodes.push_back(node2);
                m_data.push_back(Node(node2));
                m_data[size].setIndex(size);
                m_data[findNode(node1)].appendNeighbour(size);

                increaseSize(Atable, max, size);
                Atable[findNode(node1)][size] = val;
                size = max;
                continue;
            }

            if (std::find(nodes.begin(), nodes.end(), node1) == nodes.end() && std::find(nodes.begin(), nodes.end(), node2) != nodes.end()) {
                max += 1;
                nodes.push_back(node1);
                m_data.push_back(Node(node1));
                m_data[size].setIndex(size);
                m_data[size].appendNeighbour(findNode(node2));

                increaseSize(Atable, max, size);
                Atable[size][findNode(node2)] = val;
                size = max;
                continue;
            }

            if (std::find(nodes.begin(), nodes.end(), node1) != nodes.end() && std::find(nodes.begin(), nodes.end(), node2) != nodes.end()) {
                m_data[findNode(node1)].appendNeighbour(findNode(node2));
                Atable[findNode(node1)][findNode(node2)] = val;
                continue;
            }
        }
    }

    int findNode(char node_val) {
        for (int i = 0; i < m_data.size(); i++) {
            if (m_data[i].getValue() == node_val) {
                return i;
            }
        }
    }
};

bool cmp(Node node1, Node node2) {
    return (node1.getTotalValue() >= node2.getTotalValue());
}

int findMinNode(std::vector<Node>& nodes, std::vector<int>& arr) {
    int min_index = arr[0];
    for (int i = 0; i < arr.size(); i++) {
        if (nodes[arr[i]].getTotalValue() < nodes[min_index].getTotalValue()) {
            min_index = arr[i];
            continue;
        }

        if (nodes[arr[i]].getTotalValue() == nodes[min_index].getTotalValue()) {
            if (nodes[arr[i]].getValue() > nodes[min_index].getValue()) {
                min_index = arr[i];
            }
        }
    }

    return min_index;
}
void makePath(std::vector<Node>& nodes, std::vector<char>& path, int finish) {
    int cur_index = finish;
    while (cur_index != -1) {
        path.insert(path.begin(), nodes[cur_index].getValue());
        cur_index = nodes[cur_index].getCameFrom();
    }
}

std::vector<char> Astar(Graph graph, int start, int finish, int**& Atable) {
    std::vector<int> closed_set;
    std::vector<int> open_set;
    std::vector<char> path;

    graph.m_data[start].setPathVal(0);
    graph.m_data[start].calcEveristic(graph.m_data[finish].getValue());
    graph.m_data[start].calcTotalValue();

    open_set.push_back(start);

    while (!open_set.empty())
    {
        int cur_node_index = findMinNode(graph.m_data, open_set);
        if (cur_node_index == finish) {
            makePath(graph.m_data, path, finish);
            return path;
        }

        for (int i = 0; i < graph.m_data[cur_node_index].m_neighbours.size(); i++) {
            int cur_neighbour = graph.m_data[cur_node_index].m_neighbours[i];

            float temporal_path_val = graph.m_data[cur_node_index].getPathValue() + Atable[cur_node_index][cur_neighbour];
            bool need_update = false;

            if (std::find(open_set.begin(), open_set.end(), cur_neighbour) == open_set.end()) {
                open_set.push_back(cur_neighbour);
            }

            if (temporal_path_val < graph.m_data[cur_neighbour].getPathValue()) {
                need_update = true;
            }
            else {
                need_update = false;
            }

            if (need_update) {
                graph.m_data[cur_neighbour].setCameFrom(cur_node_index);
                graph.m_data[cur_neighbour].setPathVal(temporal_path_val);
                graph.m_data[cur_neighbour].calcEveristic(graph.m_data[finish].getValue());
                graph.m_data[cur_neighbour].calcTotalValue();
            }
        }
        graph.m_data[cur_node_index].m_neighbours.clear();

        int cur_node_index_copy = cur_node_index;
        closed_set.push_back(cur_node_index_copy);
        open_set.erase(std::find(open_set.begin(), open_set.end(), cur_node_index));
    }
}

int main() {
    int start, finish;
    int** Atable = nullptr;
    char ch1, ch2;

    cin >> ch1 >> ch2;

    Graph graph(Atable);
    start = graph.findNode(ch1);
    finish = graph.findNode(ch2);
    for (int i = 0; i < graph.m_data.size(); i++) {
        for (int j = 0; j < graph.m_data.size(); j++) {
            cout << Atable[i][j] << ' ';
        }
        cout << '\n';
    }
    std::vector<char> path = Astar(graph, start, finish, Atable);
    for (int i = 0; i < path.size(); i++) {
        cout << path[i];
    }
    cout << '\n';

    return 0;
}
