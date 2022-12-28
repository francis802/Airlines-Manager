#ifndef NETWORKMANAGER_GRAPH_H
#define NETWORKMANAGER_GRAPH_H


#include <list>
#include <vector>
#include <queue>
#include "Airline.h"
#include "Airport.h"

class Graph {
private:
    struct Edge{
        int dest;
        const Airline* airline;
    };

    struct Node{
        list<Edge> adj;
        bool visited;

        int dist;
        int path;
    };

    int n;
    vector<Node> nodes;

public:
    Graph();
    Graph(int num);

    void addFlight(int src, int dest, const Airline* airline);

    void bfs(queue<int> q);

    vector<Node> getNodes();
};


#endif //NETWORKMANAGER_GRAPH_H
