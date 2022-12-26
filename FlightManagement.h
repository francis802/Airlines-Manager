#ifndef NETWORKMANAGER_FLIGHTMANAGEMENT_H
#define NETWORKMANAGER_FLIGHTMANAGEMENT_H

#include <unordered_map>
#include <unordered_set>

#include "Airport.h"
#include "Airline.h"

using namespace std;

class FlightManagement {
public:
    FlightManagement();

    void getDataAirport(string filename);
    void getDataAirline(string filename);

private:
    unordered_map<Airport,int, AirportHash> airport_node;
    unordered_set<Airline, AirlineHash> airlines;
    unordered_map<string, Airport*> city_airports;
};


#endif //NETWORKMANAGER_FLIGHTMANAGEMENT_H
