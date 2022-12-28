#include <queue>
#include "Graph.h"

Graph::Graph() {}
Graph::Graph(int num): n(num), nodes(num+1) {}

void Graph::addFlight(int src, int dest, const Airline* airline) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, airline});
}

void Graph::bfs(queue<int> q) {
    for (int i=1; i<=n; i++) {
        nodes[i].visited = false;
        nodes[i].dist = -1;
        nodes[i].path = -1;
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (nodes[u].path != -1)
            nodes[u].dist = nodes[nodes[u].path].dist + 1;
        else{
            nodes[u].visited = true;
            nodes[u].dist = 0;
        }
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].path = u;
            }
        }
    }
}

vector<Graph::Node> Graph::getNodes() {
    return nodes;
}