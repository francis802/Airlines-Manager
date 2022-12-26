#include <fstream>
#include <sstream>
#include "FlightManagement.h"

FlightManagement::FlightManagement(string airports, string airlines, string flights) {
    int num_airports = getDataAirport(airports);
    this->flights = Graph(num_airports);
    getDataAirline(airlines);
    getDataFlights(flights);
}

int FlightManagement::getDataAirport(string filename) {
    ifstream in(filename);
    string line;
    getline(in, line);
    int node = 1;
    while (getline(in, line)){
        istringstream iss(line);
        string code, name, city, country, latitude, longitude;
        getline(iss, code, ',');
        getline(iss, name, ',');
        getline(iss, city, ',');
        getline(iss, country, ',');
        getline(iss, latitude, ',');
        getline(iss, longitude, '\n');

        Airport airport = Airport(code, name, city, country, stod(latitude), stod(longitude));
        const Airport* airport_pointer = &(*(airport_node.insert({airport,node}).first)).first;

        auto it = city_airports.find(city);
        if (it == city_airports.end())
            city_airports.insert({city,{airport_pointer}});
        else
            (*it).second.push_back(airport_pointer);

        node++;
    }
    return node - 1;
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

void FlightManagement::getDataFlights(string filename) {
    ifstream in(filename);
    string line;
    getline(in, line);
    while (getline(in, line)){
        istringstream iss(line);
        string source, target, airline;
        getline(iss, source, ',');
        getline(iss, target, ',');
        getline(iss, airline, '\n');

        int src = airport_node.find(Airport(source))->second;
        int dest = airport_node.find(Airport(target))->second;
        const Airline* a = &(*(airlines.find(Airline(airline))));

        flights.addFlight(src,dest, a);
    }
}

const unordered_map<Airport, int, AirportHash> &FlightManagement::getAirportNode() const {
    return airport_node;
}

const unordered_set<Airline, AirlineHash> &FlightManagement::getAirlines() const {
    return airlines;
}

const unordered_map<string, list<const Airport *>> &FlightManagement::getCityAirports() const {
    return city_airports;
}

const Graph &FlightManagement::getFlights() const {
    return flights;
}
