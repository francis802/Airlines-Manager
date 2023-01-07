#ifndef NETWORKMANAGER_MENUNETWORKSTATS_H
#define NETWORKMANAGER_MENUNETWORKSTATS_H

#include "Menu.h"

class MenuNetworkStats: public Menu {
public:
    explicit MenuNetworkStats(const FlightManagement& management);

    bool start();
    bool globalStatsMenu();
    bool countryStatsMenu();

    void globalArticulationPoints();
};

#endif //NETWORKMANAGER_MENUNETWORKSTATS_H
