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
    bool continentalStatsMenu();
    bool countryStatsMenu();

    void globalArticulationPoints();
    void continentalArticulationPoints(int option);
    void countryArticulationPoints(string country);

    unordered_set<string> getCountriesOf(const string& continent);
};

#endif //NETWORKMANAGER_MENUNETWORKSTATS_H
