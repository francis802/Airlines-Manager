#ifndef NETWORKMANAGER_GRAPH_H
#define NETWORKMANAGER_GRAPH_H


#include <list>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
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
        vector<int> path;


        int num;
        int low;
        bool inStack;
        bool isAP;
    };

    int n;
    vector<Node> nodes;

public:
    Graph();
    Graph(int num);

    void addFlight(int src, int dest, const Airline* airline);

    void bfs(queue<int> q, unordered_set<string> preferences);
    void dfs_art(int v, stack<int> *S, int index);
    vector<int> getGlobalArticulationPoints();
    vector<int> getContinentalArticulationPoints(unordered_map<int, const Airport*> map, unordered_set<string> countries);
    vector<int> getCountryArticulationPoints(unordered_map<int, const Airport*> map, string country);

    vector<int> getDistances(int u);
    int getGlobalDiameter();

    vector<Node> getNodes();
};


#endif //NETWORKMANAGER_GRAPH_H
