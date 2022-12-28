#ifndef NETWORKMANAGER_FLIGHTMANAGEMENT_H
#define NETWORKMANAGER_FLIGHTMANAGEMENT_H

#include <unordered_map>
#include <unordered_set>

#include "Airport.h"
#include "Airline.h"
#include "Graph.h"

using namespace std;

class FlightManagement {
public:
    FlightManagement(string airports, string airlines, string flights);

    int getDataAirport(string filename);
    void getDataAirline(string filename);
    void getDataFlights(string filename);

    const unordered_map<Airport, int, AirportHash> &getAirportNode() const;
    const unordered_map<int, const Airport *> &getNodeAirport() const;
    const unordered_set<Airline, AirlineHash> &getAirlines() const;
    const unordered_map<string, list<const Airport *>> &getCityAirports() const;
    Graph &getFlights();

private:
    unordered_map<Airport,int, AirportHash> airport_node;
    unordered_map<int, const Airport*> node_airport;
    unordered_set<Airline, AirlineHash> airlines;
    unordered_map<string, list<const Airport*>> city_airports;

    Graph flights;
};


#endif //NETWORKMANAGER_FLIGHTMANAGEMENT_H
