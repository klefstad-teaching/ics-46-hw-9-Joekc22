#include "dijkstras.h"

int main(){
    Graph G;
    file_to_graph("src/small.txt", G);
    int source = 0;

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);

    for (int target = 0; target < G.numVertices; ++target){
        vector<int> s_path = extract_shortest_path(distances, previous, target);
        print_path(s_path, distances[target]);
    }

    return 1;
}