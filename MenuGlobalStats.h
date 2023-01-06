#ifndef NETWORKMANAGER_MENUGLOBALSTATS_H
#define NETWORKMANAGER_MENUGLOBALSTATS_H

#include "Menu.h"

class MenuGlobalStats: public Menu {
public:
    explicit MenuGlobalStats(const FlightManagement& management);

    bool start();
    void articulationPoints();
};

#endif //NETWORKMANAGER_MENUGLOBALSTATS_H
