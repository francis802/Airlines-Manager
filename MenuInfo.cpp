#include "MenuInfo.h"

MenuInfo::MenuInfo(const FlightManagement &management): Menu(management) {}

bool MenuInfo::start() {
    auto airports = management.getAirportNode();
    string option;
    while (true) {
        cout << "-> INFO AIRPORTS\n\n";
        cout << "1 - CODE\n";
        cout << "2 - NAME\n";
        cout << "3 - CITY\n";
        cout << "4 - COUNTRY\n";
        cout << "5 - LOCATION RANGE\n";

        cout << "\n type 'q' to quit, 'r' to return\n";
        cout << "==================================================\n";
        getline(cin, option);
        if (option == "1") airportByCode(airports);
        if (option == "2") airportByName(airports);
        if (option == "3") airportByCity(airports);
        if (option == "4") airportByCountry(airports);
        if (option == "r") return false;
        if (option == "q") return true;
    }
}

void MenuInfo::printAirportInfo(Airport airport){
    cout << "\nCode: " << airport.getCode() << "\n"
    << "Name: " << airport.getName() << "\n"
    << "City: " << airport.getCity() << "\n"
    << "Country: " << airport.getCountry() << "\n"
    << "Latitude: " << airport.getLatitude() << "\n"
    << "Longitude: " << airport.getLongitude() << "\n"
    << "\n";
}

void MenuInfo::airportByCode(unordered_map<Airport, int, AirportHash> airports) {
    string code;
    cout << "Airport Code: ";
    getline(cin, code);
    Airport airport = Airport(code);
    auto verify = airports.find(airport);
    if (verify != airports.end())
        printAirportInfo(verify->first);
    else cout << "No airport with such code\n";
}

void MenuInfo::airportByName(unordered_map<Airport, int, AirportHash> airports) {
    bool found = false;
    string name;
    cout << "Airport Name: ";
    getline(cin, name);
    for (const auto& airport : airports){
        if (airport.first.getName() == name){
            printAirportInfo(airport.first);
            found = true;
        }
    }
    if(!found) cout << "No airport with such name\n";
}

void MenuInfo::airportByCity(unordered_map<Airport, int, AirportHash> airports) {
    bool found = false;
    string city;
    cout << "City: ";
    getline(cin, city);
    for (const auto& airport : airports){
        if (airport.first.getCity() == city){
            printAirportInfo(airport.first);
            found = true;
        }
    }
    if(!found) cout << "City doesn't have airports\n";
}

void MenuInfo::airportByCountry(unordered_map<Airport, int, AirportHash> airports) {
    bool found = false;
    string country;
    cout << "Country: ";
    getline(cin, country);
    for (const auto& airport : airports){
        if (airport.first.getCountry() == country){
            printAirportInfo(airport.first);
            found = true;
        }
    }
    if(!found) cout << "Country doesn't have airports\n";
}