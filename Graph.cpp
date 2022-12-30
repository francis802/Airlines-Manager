#include <queue>
#include <unordered_set>
#include "Graph.h"

Graph::Graph() {}
Graph::Graph(int num): n(num), nodes(num+1) {}

void Graph::addFlight(int src, int dest, const Airline* airline) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, airline});
}

void Graph::bfs(queue<int> q, unordered_set<string> preferences) {
    for (int i=1; i<=n; i++) {
        nodes[i].visited = false;
        nodes[i].dist = -1;
        nodes[i].path = {};
    }

    for (int i = 0; i < q.size(); i++){
        nodes[q.front()].visited = true;
        nodes[q.front()].dist = 0;
        q.push(q.front());
        q.pop();
    }

    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (!nodes[u].path.empty())
            nodes[u].dist = nodes[nodes[u].path.front()].dist + 1;
    
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (preferences.empty() || preferences.find(e.airline->getCode()) != preferences.end()) {
                if (!nodes[w].visited) {
                    q.push(w);
                    nodes[w].visited = true;
                    nodes[w].path.push_back(u);
                } else if (!nodes[w].path.empty() && nodes[nodes[w].path.front()].dist == nodes[u].dist) {
                    bool repeat = false;
                    for (int i : nodes[w].path)
                        if (i == u) {
                            repeat = true;
                            break;
                        }
                    if (!repeat)
                        nodes[w].path.push_back(u);
                }
            }
        }
    }
}

vector<Graph::Node> Graph::getNodes() {
    return nodes;
}