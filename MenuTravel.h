#ifndef NETWORKMANAGER_MENUTRAVEL_H
#define NETWORKMANAGER_MENUTRAVEL_H


#include <list>
#include "Menu.h"

class MenuTravel: public Menu {
public:
    explicit MenuTravel(const FlightManagement& management);

    bool start();

    list<Airport> getAirports();
};


#endif //NETWORKMANAGER_MENUTRAVEL_H
