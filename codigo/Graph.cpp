#include <queue>
#include <unordered_set>
#include <stack>
#include <set>
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

void Graph::dfs_art(int v, stack<int> *S, int index) {
    nodes[v].num = index; nodes[v].low = index;
    index++;
    int children = 0;
    S->push(v); nodes[v].inStack = true;
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (nodes[w].num == -1) {
            children++;
            dfs_art(w, S, index);
            nodes[v].low = min(nodes[v].low, nodes[w].low);
            if (S->size() != 1 && nodes[w].low >= nodes[v].num)
                nodes[v].isAP = true;
        }
        else if (nodes[w].inStack) {
            nodes[v].low = min(nodes[v].low, nodes[w].num);
        }
    }
    if (S->size() == 1 && children > 1)
        nodes[v].isAP = true;
    int temp = S->top();
    S->pop();
    nodes[temp].inStack = false;
}

vector<int> Graph::getGlobalArticulationPoints() {
    stack<int> S;
    vector<int> result;
    int index = 1;
    for (int v = 1; v <= n; v++) {
        nodes[v].num = -1;
        nodes[v].low = -1;
        nodes[v].inStack = false;
        nodes[v].isAP = false;
    }
    for (int v = 1; v <= n; v++) {
        if (nodes[v].num == -1) {
            dfs_art(v, &S, index);
        }
    }
    for (int v = 1; v<=n; v++) {
        if (nodes[v].isAP)
            result.push_back(v);
    }
    return result;
}

vector<int> Graph::getContinentalArticulationPoints(unordered_map<int, const Airport*> map, unordered_set<string> countries) {
    stack<int> S;
    vector<int> result;
    int index = 1;
    for (int v = 1; v <= n; v++) {
        if (countries.find(map[v]->getCountry()) == countries.end()){
            nodes[v].num = -2;
        }
        else nodes[v].num = -1;
        nodes[v].low = -1;
        nodes[v].inStack = false;
        nodes[v].isAP = false;
    }
    for (int v = 1; v <= n; v++) {
        if (nodes[v].num == -1) {
            dfs_art(v, &S, index);
        }
    }
    for (int v = 1; v<=n; v++) {
        if (nodes[v].isAP)
            result.push_back(v);
    }
    return result;
}

vector<int> Graph::getCountryArticulationPoints(unordered_map<int, const Airport*> map, string country) {
    stack<int> S;
    vector<int> result;
    int index = 1;
    for (int v = 1; v <= n; v++) {
        if (map[v]->getCountry() != country){
            nodes[v].num = -2;
        }
        else nodes[v].num = -1;
        nodes[v].low = -1;
        nodes[v].inStack = false;
        nodes[v].isAP = false;
    }
    for (int v = 1; v <= n; v++) {
        if (nodes[v].num == -1) {
            dfs_art(v, &S, index);
        }
    }
    for (int v = 1; v<=n; v++) {
        if (nodes[v].isAP)
            result.push_back(v);
    }
    return result;
}

int Graph::getMaxDistance(int u) {
    for (int i=1; i<=n; i++) {
        nodes[i].visited = false;
        nodes[i].dist = -1;
    }
    int maxDistance = 0;
    queue<int> Q;
    nodes[u].dist = 0;
    Q.push(u);
    nodes[u].visited = true;
    while (!Q.empty()) {
        int x = Q.front();
        Q.pop();
        for (auto e : nodes[x].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                nodes[w].dist = nodes[x].dist + 1;
                Q.push(w);
                nodes[w].visited = true;
                if (nodes[w].dist>maxDistance)
                    maxDistance = nodes[w].dist;
            }
        }
    }
    return maxDistance;
}

int Graph::getGlobalDiameter() {
    int max = 0;
    for (int i = 1; i <= n; i++) {
        int d = getMaxDistance(i);
        if (d > max) {
            max = d;
        }
    }
    return max;
}