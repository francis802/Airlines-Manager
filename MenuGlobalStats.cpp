#include "MenuGlobalStats.h"

#include <stack>
#include <set>

MenuGlobalStats::MenuGlobalStats(const FlightManagement &management): Menu(management) {}

bool MenuGlobalStats::start() {
    bool exit = false;
    string option;
    while (!exit) {
        cout << "-> GLOBAL STATS\n\n";
        cout << "1 - ARTICULATION POINTS\n";

        cout << "\n type 'q' to quit, 'r' to return\n";
        cout << "==================================================\n";
        getline(cin, option);
        if (option == "1")
            articulationPoints();
        else if (option == "r") return false;
        else if (option == "q") return true;
        else cout << "Invalid input\n";
    }
    return true;
}

void dfs_art(int v, vector<bool> *inStack, vector<int> *num, vector<int> *low, stack<int> *S, int index, set<int> *result, Graph graph) {
    (*num)[v] = index; (*low)[v] = index;
    index++;
    int children = 0;
    S->push(v); (*inStack)[v] =true;
    for (auto e : (graph.getNodes())[v].adj) {
        int w = e.dest;
        if ((*num)[w] == -1) {
            children++;
            dfs_art(w, inStack, num, low, S, index, result, graph);
            (*low)[v] = min((*low)[v], (*low)[w]);
            if (S->size() != 1 && (*low)[w] >= (*num)[v])
                result->insert(v);
        }
        else if ((*inStack)[w]) {
            (*low)[v] = min((*low)[v], (*num)[w]);
        }
    }
    if (S->size() == 1 && children > 1)
        result->insert(v);
    int temp = S->top();
    S->pop();
    (*inStack)[temp] = false;
}

void MenuGlobalStats::articulationPoints() {
    Graph graph = management.getFlights();
    int n = graph.getNodes().size();
    vector<bool> inStack;
    inStack.push_back(false);
    vector<int> num;
    num.push_back(-1);
    vector<int> low;
    low.push_back(-1);
    stack<int> S;
    set<int> result;
    int index = 1;
    for (int v = 1; v <= n; v++) {
        num.push_back(-1);
        low.push_back(-1);
        inStack.push_back(false);
    }
    for (int v = 1; v <= n; v++) {
        if (num[v] == -1) {
            dfs_art(v, &inStack, &num, &low, &S, index, &result, graph);
        }
    }
    cout << "Number of articulation points: " << result.size() << "\n";
    for (int i : result) {
        cout << i << "\n";
    }
}