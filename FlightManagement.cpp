#include <fstream>
#include <sstream>
#include "FlightManagement.h"

FlightManagement::FlightManagement() {}

void FlightManagement::getDataAirport(string filename) {
    ifstream in(filename);
    string line;
    getline(in, line);
    int node = 1;
    while (getline(in, line)){
        istringstream iss(line);
        string code, name, city, latitude, longitude;
        getline(iss, code, ',');
        getline(iss, name, ',');
        getline(iss, city, ',');
        getline(iss, latitude, ',');
        getline(iss, longitude, '\n');

        Airport airport = Airport(code, name, city, stod(latitude), stod(longitude));
        airport_node.insert({airport,node});
        node++;
    }
}

void FlightManagement::getDataAirline(string filename) {
    ifstream in(filename);
    string line;
    getline(in, line);
    while (getline(in, line)){
        istringstream iss(line);
        string code, name, callsign, country;
        getline(iss, code, ',');
        getline(iss, name, ',');
        getline(iss, callsign, ',');
        getline(iss, country, '\n');

        Airline airline = Airline(code, name, callsign, country);
        airlines.insert(airline);
    }
}
