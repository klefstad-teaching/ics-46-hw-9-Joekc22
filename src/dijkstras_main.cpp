#include "dijkstras.h"

int main(){
    Graph graph;
    file_to_graph("src/small.txt", graph);
    int source = 0;
    vector<int> previous;
    vector<int> dist = dijkstra_shortest_path(graph, source, previous);


    for (int target = 0; target < graph.numVertices; ++target){
        vector<int> s_path = extract_shortest_path(dist, previous, target);
        print_path(s_path, dist[target]);
    }

    return 1;
}