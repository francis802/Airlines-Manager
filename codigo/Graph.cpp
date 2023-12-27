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

void Graph::dfs_cc(int v) {
    nodes[v].visited = true;
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited)
            dfs_cc(w);
    }
}

void Graph::dfs_scc(int v, stack<int> *S, int index, list<list<int>> *result) {
    nodes[v].num = index; nodes[v].low = index;
    index++;
    S->push(v); nodes[v].inStack = true;
    for (auto e:nodes[v].adj){
        int w = e.dest;
        if (nodes[w].num == -1){
            dfs_scc(w,S,index, result);
            nodes[v].low = min(nodes[v].low,nodes[w].low);
        }
        else if (nodes[w].inStack){
            nodes[v].low = min(nodes[v].low,nodes[w].num);
        }
    }
    if (nodes[v].num == nodes[v].low){
        list<int> temp;
        int w = S->top();
        S->pop(); nodes[w].inStack = false;
        temp.push_back(w);
        while (w != v){
            w = S->top();
            S->pop(); nodes[w].inStack = false;
            temp.push_back(w);
        }
        result->push_back(temp);
    }
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

pair<int,int> Graph::getMaxDistance(int u, unordered_map<int, const Airport *> map, unordered_set<std::string> countries) {
    if (map.empty() && countries.empty()){
        for (int i=1; i<=n; i++){
            nodes[i].visited = false;
            nodes[i].dist = -1;
        }
    }
    else {
        for (int i=1; i<=n; i++) {
            if (countries.find(map[i]->getCountry()) == countries.end())
                nodes[i].visited = true;
            else
                nodes[i].visited = false;
            nodes[i].dist = -1;
        }
    }
    int maxDistance = 0;
    int mostDistantNode = -1;
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
                if (nodes[w].dist > maxDistance) {
                    maxDistance = nodes[w].dist;
                    mostDistantNode = w;
                }
            }
        }
    }
    return {maxDistance, mostDistantNode};
}

pair<int,vector<pair<int,int>>> Graph::getGlobalDiameter() {
    int max = 0;
    vector<pair<int,int>> source_dest_pairs;
    for (int i = 1; i <= n; i++) {
        pair<int,int> pair = getMaxDistance(i);
        if (pair.first > max) {
            max = pair.first;
            source_dest_pairs.clear();
            source_dest_pairs.push_back({i,pair.second});
        }
        else if (pair.first == max) {
            source_dest_pairs.push_back({i,pair.second});
        }
    }
    return {max,source_dest_pairs};
}

pair<int,vector<pair<int,int>>> Graph::getContinentalDiameter(unordered_map<int, const Airport *> map, unordered_set<std::string> countries) {
    int max = 0;
    vector<pair<int,int>> source_dest_pairs;
    for (int i = 1; i <= n; i++) {
        if (countries.find(map[i]->getCountry()) != countries.end()) {
            pair<int,int> pair = getMaxDistance(i, map, countries);
            if (pair.first > max) {
                max = pair.first;
                source_dest_pairs.clear();
                source_dest_pairs.push_back({i,pair.second});
            }
            else if (pair.first == max) {
                source_dest_pairs.push_back({i,pair.second});
            }
        }
    }
    return {max,source_dest_pairs};
}

pair<int,vector<pair<int,int>>> Graph::getCountryDiameter(unordered_map<int, const Airport *> map, std::string country) {
    int max = 0;
    vector<pair<int,int>> source_dest_pairs;
    unordered_set<std::string> countries;
    countries.insert(country);
    for (int i = 1; i <= n; i++) {
        if (countries.find(map[i]->getCountry()) == countries.end()) {
            continue;
        }
        pair<int,int> pair = getMaxDistance(i, map, countries);
        if (pair.first > max) {
            max = pair.first;
            source_dest_pairs.clear();
            source_dest_pairs.push_back({i,pair.second});
        }
        if (pair.first == max) {
            source_dest_pairs.push_back({i,pair.second});
        }
    }
    return {max,source_dest_pairs};
}

int Graph::getGlobalConnectedComponents() {
    int count = 0;
    for (int v=1;v <= n; v++){
        nodes[v].visited = false;
    }
    for (int v = 1; v <= n; v++) {
        if (!nodes[v].visited) {
            count++;
            dfs_cc(v);
        }
    }
    return count;
}

int Graph::getContinentalConnectedComponents(unordered_map<int, const Airport *> map, unordered_set<std::string> countries) {
    int count = 0;
    for (int v=1;v <= n; v++){
        if (countries.find(map[v]->getCountry()) == countries.end())
            nodes[v].visited = true;
        else
            nodes[v].visited = false;
    }
    for (int v = 1; v <= n; v++) {
        if (!nodes[v].visited) {
            count++;
            dfs_cc(v);
        }
    }
    return count;
}

int Graph::getCountryConnectedComponents(unordered_map<int, const Airport *> map, std::string country) {
    int count = 0;
    for (int v=1;v <= n; v++){
        if (map[v]->getCountry() == country)
            nodes[v].visited = true;
        else
            nodes[v].visited = false;
    }
    for (int v = 1; v <= n; v++) {
        if (!nodes[v].visited) {
            count++;
            dfs_cc(v);
        }
    }
    return count;
}

list<list<int>> Graph::getGlobalSCC() {
    stack<int> S;
    list<list<int>> result;
    int index = 1;
    for (int v=1; v<=n; v++){
        nodes[v].num = -1;
        nodes[v].low = -1;
        nodes[v].inStack = false;
    }
    for (int v=1; v<=n; v++){
        if (nodes[v].num == -1){
            dfs_scc(v, &S, index, &result);
        }
    }
    return result;
}

list<list<int>> Graph::getContinentalSCC(unordered_map<int, const Airport *> map, unordered_set<string> countries) {
    stack<int> S;
    list<list<int>> result;
    int index = 1;
    for (int v=1; v<=n; v++){
        if (countries.find(map[v]->getCountry()) == countries.end()){
            nodes[v].num = -2;
        }
        else nodes[v].num = -1;
        nodes[v].low = -1;
        nodes[v].inStack = false;
    }
    for (int v=1; v<=n; v++){
        if (nodes[v].num == -1){
            dfs_scc(v, &S, index, &result);
        }
    }
    return result;
}

list<list<int>> Graph::getCountrySCC(unordered_map<int, const Airport *> map, string country) {
    stack<int> S;
    list<list<int>> result;
    int index = 1;
    for (int v=1; v<=n; v++){
        if (map[v]->getCountry() != country){
            nodes[v].num = -2;
        }
        else nodes[v].num = -1;
        nodes[v].low = -1;
        nodes[v].inStack = false;
    }
    for (int v=1; v<=n; v++){
        if (nodes[v].num == -1){
            dfs_scc(v, &S, index, &result);
        }
    }
    return result;
}

vector<pair<int,int>> Graph::topBusiestAirports() {
    vector<pair<int,int>> flights_in_out;
    flights_in_out.push_back({0,-1});
    for(int i=1; i<=n; i++){
        flights_in_out.push_back({i,0});
    }

    for(int i=1; i<=n; i++){
        auto source = &flights_in_out[i];
        source->second += nodes[i].adj.size();
        for(auto it = nodes[i].adj.begin(); it != nodes[i].adj.end(); it++){
            auto dest = &flights_in_out[it->dest];
            dest->second += 1;
        }
    }

    sort(flights_in_out.begin(), flights_in_out.end(), [](pair<int,int>p1,pair<int,int>p2){
        return p1.second>p2.second;
    });

    return flights_in_out;
}

vector<pair<const Airline*, int>> Graph::getFlightsPerAirline(){
    unordered_map<const Airline*, int> map;

    for(int v=1; v<=n; v++){
        for(auto it = nodes[v].adj.begin(); it != nodes[v].adj.end(); it++){
            auto finder = map.find(it->airline);
            if (finder == map.end()){
                map.insert({it->airline, 1});
            }
            else {
                finder->second++;
            }

        }
    }
    vector<pair<const Airline*, int>> flights_airline(map.begin(), map.end());
    sort(flights_airline.begin(), flights_airline.end(), [](pair<const Airline*, int>p1,pair<const Airline*, int>p2){
        return p1.second > p2.second;
    });
    return flights_airline;
}

vector<pair<string, int>> Graph::getFlightsPerCity(unordered_map<int, const Airport*> airports){
    unordered_map<string, int> map;

    for(int v=1; v<=n; v++){
        auto source = map.find(airports.find(v)->second->getCity());
        if(source == map.end()){
            map.insert({airports.find(v)->second->getCity(), nodes[v].adj.size()});
        }
        else{
            source->second += nodes[v].adj.size();
        }
        for(auto it = nodes[v].adj.begin(); it != nodes[v].adj.end(); it++){
            auto dest = map.find(airports.find(it->dest)->second->getCity());
            if (dest == map.end()){
                map.insert({airports.find(it->dest)->second->getCity(), 1});
            }
            else {
                dest->second++;
            }

        }
    }
    vector<pair<string, int>> flights_airline(map.begin(), map.end());
    sort(flights_airline.begin(), flights_airline.end(), [](pair<string, int>p1,pair<string, int>p2){
        return p1.second > p2.second;
    });
    return flights_airline;
}