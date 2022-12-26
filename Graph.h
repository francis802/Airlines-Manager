#ifndef NETWORKMANAGER_GRAPH_H
#define NETWORKMANAGER_GRAPH_H


#include <list>
#include <vector>
#include "Airline.h"

class Graph {
private:
    struct Edge{
        int dest;
        const Airline* airline;
    };

    struct Node{
        list<Edge> adj;
        bool visited;
    };

    int n;
    vector<Node> nodes;

public:
    Graph(int nodes);

    void addFlight(int src, int dest, const Airline* airline);
};


#endif //NETWORKMANAGER_GRAPH_H
