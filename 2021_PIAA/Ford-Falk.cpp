#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using std::cout;
using std::cin;

class Edge {
private:
    char m_end = 0;
    int m_size = 0;
    int m_flow = 0;

public:
    Edge(char end = 0, int size = 0, int flow = 0): m_end(end), m_size(size), m_flow(flow) {}
    Edge() {}
    
    void set_end(char end) {
        m_end = end;
    }

    void change_size(int delta) {
        m_size += delta;
    }

    void change_flow(int delta) {
        m_flow += delta;
    }

    char get_end() {
        return m_end;
    }

    int get_size() {
        return m_size;
    }

    int get_flow() {
        return m_flow;
    }
};

class Node {
public:
    char m_prev = 0;
    char m_name = 0;
    bool m_is_visited = false;
    std::vector<Edge> m_edges;
public:
    Node(char prev = 0, char name = 0, bool visited = false) : m_prev(prev), m_name(name), m_is_visited(visited) {}

    void addEdge(char end, int size) {
        m_edges.push_back(Edge(end, size, 0));
    }
};

bool lex_cmp(Edge edge1, Edge edge2) {//edges sorting by end names
    return edge1.get_end() < edge2.get_end();
}

void printGraph(std::map<char, Node> graph) {
    for (std::pair<char, Node> node : graph) {
        std::sort(graph[node.first].m_edges.begin(), graph[node.first].m_edges.end(), lex_cmp);
        for (Edge edge : node.second.m_edges) {
            cout << node.first << ' ' << edge.get_end() << ' ' << std::max(0, edge.get_flow()) << '\n';
        }
    }
}

std::map<char, Node> readGraph(int size) {
    std::map<char, Node> graph;
    char a, b;
    int c = 0;;
    for (int i = 0; i < size; i++) {
        cin >> a >> b >> c;
        if (graph.find(a) == graph.end()) {
            graph.emplace(a, Node(0, a, false));
            graph[a].addEdge(b, c);
        }
        else {
            graph[a].addEdge(b, c);
        }
    }
    return graph;
}

char getNextNode(std::map<char, Node> graph, char node) {
    for (Edge edge : graph[node].m_edges) {
        if (!graph[edge.get_end()].m_is_visited  && edge.get_size() > 0) {
            return edge.get_end();
        }
    }

    return 0;
}

bool cap_cmp(Edge edge1, Edge edge2) {//edges sorting by capacity
    if (edge1.get_size() == edge2.get_size()) {
        return edge1.get_end() < edge2.get_end();
    }
    return edge1.get_size() < edge2.get_size();
}

void printPath(std::vector<char> path) {
    cout << "Current path is:\n";
    for (char elem : path) {
        cout << elem << ' ';
    }
    cout << '\n';
}

std::vector<char> dfs(std::map<char, Node> graph, char begin, char end){
    cout << "Finding path from " << begin << " to " << end << " by using DFS:\n";
    std::vector<char> path;
    path.push_back(begin);
    char cur_node = begin;
    cout << "Add start node to path\n";
    printPath(path);
    
    for (std::pair<char, Node> node : graph) {
        std::sort(graph[node.first].m_edges.begin(), graph[node.first].m_edges.end(), cap_cmp);
    }

    while ((cur_node != end) && !path.empty()) {
        cout << "Current node: " << cur_node << ". Let's find next node for path if it exists.\n";
        graph[cur_node].m_is_visited = true;
        char next_node = getNextNode(graph, cur_node);
        if (next_node) {
            cout << "New node in path: " << next_node << '\n';
            graph[next_node].m_prev = cur_node;
            path.push_back(next_node);
            cur_node = next_node;
            printPath(path);
        }
        else {
            cout << "Next node for path doesn't exist. Exclude current node from path.\n";
            cur_node = graph[cur_node].m_prev;
            path.erase(path.end() - 1);
            printPath(path);
        }
    }

    for (std::pair<char, Node> node : graph) {
        graph[node.first].m_is_visited = false;
    }

    return path;
}

int findFlowChange(std::map<char, Node> graph, std::vector<char> path){
    int min = 0x7FFFFFFF;
    for (int i = 0; i < path.size() - 1; i++) {
        for (Edge edge : graph[path[i]].m_edges) {
            if (edge.get_end() == path[i+1] && (edge.get_size() < min)) {
                min = edge.get_size();
            }
        }
    }

    return min;
}

void updateNet(std::map<char, Node>& graph, std::vector<char> path) {
    cout << "Update net:\n";
    int delta = findFlowChange(graph, path);
    printPath(path);
    cout << "Minimal capacity of any edge on the path is " << delta << '\n';
    cout << "Update capacity and flow for every node on the path\n";
    for (int i = 0; i < path.size() - 1; i++) {
        for (Edge& edge : graph[path[i]].m_edges) {
            if (edge.get_end() == path[i+1]) {
                cout << "Current flow and capacity of direct rib from" << path[i] << " to " << edge.get_end() << " is " << edge.get_flow() << " and " << edge.get_size() << '\n';
                edge.change_flow(delta);
                edge.change_size(-delta);
                cout << "New flow and capacity of direct rib from" << path[i] << " to " << edge.get_end() << " is " << edge.get_flow() << " and " << edge.get_size() << '\n';
                for (Edge& edge : graph[path[i+1]].m_edges) {
                    if (edge.get_end() == path[i]) {
                        cout << "Current flow and capacity of reverse rib from" << path[i+1] << " to " << edge.get_end() << " is " << edge.get_flow() << " and " << edge.get_size() << '\n';
                        edge.change_flow(-delta);
                        edge.change_size(delta);
                        cout << "New flow and capacity of reverse rib from" << path[i + 1] << " to " << edge.get_end() << " is " << edge.get_flow() << " and " << edge.get_size() << '\n';
                    }
                }
            }
        }
    }
}

int main() {
    char begin, end;
    int size;
    cin >> size >> begin >> end;
    std::map<char, Node> graph = readGraph(size);

    for (std::pair<char, Node> node : graph) {
        std::sort(graph[node.first].m_edges.begin(), graph[node.first].m_edges.end(), lex_cmp);
    }

    cout << "\nGraph as list of edges sorted in lexicographic order:\n";
    printGraph(graph);
    cout << '\n';

    std::vector<char> path = dfs(graph, begin, end);
    while (!path.empty()) {
        updateNet(graph, path);
        path = dfs(graph, begin, end);
        cout << "Current flows in graph:\n";
        printGraph(graph);
    }

    int total_flow = 0;
    for (Edge edge : graph[begin].m_edges) {
        total_flow += edge.get_flow();
    }
    cout << "\nMax flow in graph:\n";
    cout << total_flow << '\n';
    cout << "Final flows in graph:\n";
    printGraph(graph);
    return 0;
}
