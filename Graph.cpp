//
// Created by tomas on 26-12-2022.
//

#include "Graph.h"

Graph::Graph(int nodes): nodes(nodes) {}

void Graph::addFlight(int src, int dest, const Airline* airline) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, airline});
}
