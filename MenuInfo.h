#ifndef NETWORKMANAGER_MENUINFO_H
#define NETWORKMANAGER_MENUINFO_H


#include "Menu.h"

class MenuInfo: public Menu{
public:
    explicit MenuInfo(const FlightManagement &management);

    bool start();
    bool generalSearchMenu();
    bool directSearch();
    bool indirectSearch();

    void airportByCode();
    void airportByName();
    void airportByCity();
    void airportByCountry();
    void airportByLocation();
    void flightsAvailable();
    void airlinesAvailable();
    void directAirportsAvailable();
    void directDestinationsAvailable();
    void directCountriesAvailable();
    void indirectAirportsAvailable(int maxDist);
    void indirectDestinationsAvailable(int maxDist);
    void indirectCountriesAvailable(int maxDist);



    static void printAirportInfo(Airport airport);
};


#endif //NETWORKMANAGER_MENUINFO_H
