#include "MenuGlobalStats.h"

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

void MenuGlobalStats::articulationPoints() {
    Graph graph = management.getFlights();
    vector<int> aps = graph.articulationPoints();
    cout << "Number of articulation points: " << aps.size() << "\n";
    for (int i : aps) {
        cout << i << "\n";
    }
}