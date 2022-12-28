#ifndef NETWORKMANAGER_MENUTRAVEL_H
#define NETWORKMANAGER_MENUTRAVEL_H


#include <list>
#include <queue>
#include "Menu.h"

class MenuTravel: public Menu {
public:
    explicit MenuTravel(const FlightManagement& management);

    bool start();

    static double haversine(double lat1, double lon1, double lat2, double lon2);

    queue<int> getAirports();
};


#endif //NETWORKMANAGER_MENUTRAVEL_H
