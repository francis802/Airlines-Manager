#ifndef NETWORKMANAGER_MENUNETWORKSTATS_H
#define NETWORKMANAGER_MENUNETWORKSTATS_H

#include "Menu.h"
#include <unordered_map>
#include <vector>

class MenuNetworkStats: public Menu {
public:
    explicit MenuNetworkStats(const FlightManagement& management);

    bool start();
    bool globalStatsMenu();
    bool countryStatsMenu();

    void globalArticulationPoints();

    void countryArticulationPoints();

    string get_continent(const string& country);
};

#endif //NETWORKMANAGER_MENUNETWORKSTATS_H
