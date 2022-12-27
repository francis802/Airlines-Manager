#ifndef NETWORKMANAGER_MENUINFO_H
#define NETWORKMANAGER_MENUINFO_H


#include "Menu.h"

class MenuInfo: public Menu{
public:
    explicit MenuInfo(const FlightManagement &management);

    bool start();

    void printAirportsInfo(string identifier, unordered_map<Airport, int, AirportHash> airports);

    void printAirportInfo(Airport airport);
};


#endif //NETWORKMANAGER_MENUINFO_H
