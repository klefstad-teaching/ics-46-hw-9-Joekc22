#include "dijkstras.h"
#include <algorithm>
#include <vector>
#include <queue>

//g++ -std=c++20 -Wall -pedantic -g -o main src/dijkstras.cpp src/dijkstras_main.cpp
////g++ -std=c++20 -Wall -pedantic -g -o main src/ladder.cpp src/ladder_main.cpp
struct Node {
    int vertex;
    int weight;
    Node(int v,int w): vertex(v), weight(w) {}
    bool operator>(const Node& other) const {
        return weight > other.weight;
    }
};

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> distance(n, INF);
    vector<bool> visited(n, false);
    previous.assign(n, -1);
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push(Node(source, 0));
    distance[source] = 0;
    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();
        int u = current.vertex;
        if (visited[u]) {
            continue;
        }
        visited[u] = true;
        for (const Edge& e : G[u]) {
            int v = e.dst;
            int weight = e.weight;
            if (!visited[v] && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push(Node(v, distance[v]));
            }
        }
    }
    return distance;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination) {
    vector<int> s_path;
    for (int i = destination; i != -1; i = previous[i]) {
        s_path.push_back(i);
    }
    reverse(s_path.begin(), s_path.end());
    return s_path;
}

void print_path(const vector<int>& v, int total){
    if (total == INF){
        cout << "No path found." << endl;
        return;
    }
    int len = v.size();
    for (int i = 0; i < len; i++) {
        cout << v[i] << ' ';
    }
    cout << endl;
    cout << "Total cost is " << total << endl;
}