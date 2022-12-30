#include <set>
#include "MenuInfo.h"

MenuInfo::MenuInfo(const FlightManagement &management): Menu(management) {}

bool MenuInfo::start() {
    bool exit;
    string option;
    while (true) {
        cout << "-> INFO AIRPORTS\n\n";
        cout << "1 - GENERAL SEARCH\n";
        cout << "2 - FLIGHTS AVAILABLE\n";
        cout << "3 - FLIGHT COMPANIES AVAILABLE\n";
        cout << "4 - AIRPORT DIRECT REACH\n";
        cout << "5 - AIRPORT INDIRECT REACH\n";


        cout << "\n type 'q' to quit, 'r' to return\n";
        cout << "==================================================\n";
        getline(cin, option);
        if (option == "1") {
            exit = generalSearchMenu();
            if (exit) return true;
        }
        if (option == "2") flightsAvailable();
        if (option == "3") companiesAvailable();
        if (option == "4"){
            exit = directSearch();
            if (exit) return true;
        }
        if (option == "5"){

        }
        if (option == "r") return false;
        if (option == "q") return true;
    }
}

bool MenuInfo::generalSearchMenu(){
    auto airports = management.getAirportNode();
    string option;
    while (true) {
        cout << "-> SEARCH AIRPORTS BY\n\n";
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
        if (option == "5") airportByLocation(airports);
        if (option == "r") return false;
        if (option == "q") return true;
    }
}

bool MenuInfo::directSearch(){
    string option;
    while (true) {
        cout << "-> DIRECT CONNECTIONS\n\n";
        cout << "1 - AIRPORTS AVAILABLE\n";
        cout << "2 - DESTINIES AVAILABLE\n";
        cout << "3 - COUNTRIES AVAILABLE\n";

        cout << "\n type 'q' to quit, 'r' to return\n";
        cout << "==================================================\n";
        getline(cin, option);
        if (option == "1") directAirportsAvailable();
        if (option == "2") directDestiniesAvailable();
        if (option == "3") directCountriesAvailable();
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

void MenuInfo::airportByLocation(unordered_map<Airport, int, AirportHash> airports) {
    bool found = false;
    string stringInput;
    float minLat, maxLat, minLon, maxLon;
    int i = 0;
    vector<string> messages = {"Min Latitude: ", "Max Latitude: ", "Min Longitude: ", "Max Longitude: "};
    while (i<4){
        cout << '\n' << messages[i];
        getline(cin, stringInput);
        if (i == 0){
            try{
                minLat = stof(stringInput);
            }
            catch (invalid_argument){
                cout << "Invalid Input\n";
                continue;
            }
        }
        if (i == 1){
            try{
                maxLat = stof(stringInput);
            }
            catch (invalid_argument){
                cout << "Invalid Input\n";
                continue;
            }
        }
        if (i == 2){
            try{
                minLon = stof(stringInput);
            }
            catch (invalid_argument){
                cout << "Invalid Input\n";
                continue;
            }
        }
        if (i == 3){
            try{
                maxLon = stof(stringInput);
            }
            catch (invalid_argument){
                cout << "Invalid Input\n";
                continue;
            }
        }
        i++;
    }
    for (const auto& airport : airports){
        if (minLat <= airport.first.getLatitude() && airport.first.getLatitude() <= maxLat
         && minLon <= airport.first.getLongitude() && airport.first.getLongitude() <= maxLon){
            printAirportInfo(airport.first);
            found = true;
        }
    }
    if(!found) cout << "No airport in Location Range\n";
}

void MenuInfo::flightsAvailable() {
    auto flights = management.getFlights();
    int counter = 0;
    string code;
    cout << "Airport Code: ";
    getline(cin, code);
    auto node_airport = management.getAirportNode().find(Airport(code));
    int graph_pos = node_airport->second;
    auto nodes = flights.getNodes();
    auto node = nodes[graph_pos];
    for (auto it = node.adj.begin(); it != node.adj.end();it++) counter++;
    if(counter == 0) cout << "No airport with such code\n";
    else cout << "Airport " << code << " has " << counter << " flights\n";
}

void MenuInfo::companiesAvailable() {
    auto flights = management.getFlights();
    int counter = 0;
    unordered_set<string> companies;
    string code;
    cout << "Airport Code: ";
    getline(cin, code);
    auto node_airport = management.getAirportNode().find(Airport(code));
    int graph_pos = node_airport->second;
    auto nodes = flights.getNodes();
    auto node = nodes[graph_pos];
    for (auto & it : node.adj){
        if (companies.find(it.airline->getCode()) == companies.end()){
            companies.insert(it.airline->getCode());
            counter++;
        }
    }
    if(counter == 0) cout << "No airport with such code\n";
    else cout << "Airport " << code << " has " << counter << " companies\n";
}

void MenuInfo::directAirportsAvailable(){
    auto flights = management.getFlights();
    int counter = 0;
    unordered_set<string> airports;
    string code;
    cout << "Airport Code: ";
    getline(cin, code);
    auto airport_node = management.getAirportNode().find(Airport(code));
    int graph_pos = airport_node->second;
    auto nodes = flights.getNodes();
    auto node = nodes[graph_pos];
    for (auto & it : node.adj){
        auto airport = management.getNodeAirport().find(it.dest);
        if (airports.find(airport->second->getCode()) == airports.end()){
            airports.insert(airport->second->getCode());
            counter++;
        }
    }
    if(counter == 0) cout << "No airport with such code\n";
    else cout << "Airport " << code << " can directly reach " << counter << " airports\n";
}

void MenuInfo::directDestiniesAvailable(){
    auto flights = management.getFlights();
    int counter = 0;
    unordered_set<string> destinies;
    string code;
    cout << "Airport Code: ";
    getline(cin, code);
    auto airport_node = management.getAirportNode().find(Airport(code));
    int graph_pos = airport_node->second;
    auto nodes = flights.getNodes();
    auto node = nodes[graph_pos];
    for (auto & it : node.adj){
        auto airport = management.getNodeAirport().find(it.dest);
        if (destinies.find(airport->second->getCity()) == destinies.end()){
            destinies.insert(airport->second->getCity());
            counter++;
        }
    }
    if(counter == 0) cout << "No airport with such code\n";
    else cout << "Airport " << code << " can directly reach " << counter << " destinies\n";
}

void MenuInfo::directCountriesAvailable(){
    auto flights = management.getFlights();
    int counter = 0;
    unordered_set<string> countries;
    string code;
    cout << "Airport Code: ";
    getline(cin, code);
    auto airport_node = management.getAirportNode().find(Airport(code));
    int graph_pos = airport_node->second;
    auto nodes = flights.getNodes();
    auto node = nodes[graph_pos];
    for (auto & it : node.adj){
        auto airport = management.getNodeAirport().find(it.dest);
        if (countries.find(airport->second->getCountry()) == countries.end()){
            countries.insert(airport->second->getCountry());
            counter++;
        }
    }
    if(counter == 0) cout << "No airport with such code\n";
    else cout << "Airport " << code << " can directly reach " << counter << " countries\n";
}