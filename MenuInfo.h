#ifndef NETWORKMANAGER_MENUINFO_H
#define NETWORKMANAGER_MENUINFO_H


#include "Menu.h"

class MenuInfo: public Menu{
public:
    explicit MenuInfo(const FlightManagement &management);

    bool start();

    void airportByCode(unordered_map<Airport,int,AirportHash> airports);
    void airportByName(unordered_map<Airport,int,AirportHash> airports);
    void airportByCity(unordered_map<Airport,int,AirportHash> airports);
    void airportByCountry(unordered_map<Airport,int,AirportHash> airports);
    void airportByLocation(unordered_map<Airport,int,AirportHash> airports);

    static void printAirportInfo(Airport airport);
};


#endif //NETWORKMANAGER_MENUINFO_H
