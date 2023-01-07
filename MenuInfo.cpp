#include <set>
#include "MenuInfo.h"

MenuInfo::MenuInfo(const FlightManagement &management): Menu(management) {}

bool MenuInfo::start() {
    bool exit = false;
    string option;
    while (!exit) {
        cout << "-> INFO AIRPORTS\n\n";
        cout << "1 - GENERAL SEARCH\n";
        cout << "2 - FLIGHTS AVAILABLE\n";
        cout << "3 - AIRLINES AVAILABLE\n";
        cout << "4 - AIRPORT DIRECT REACH\n";
        cout << "5 - AIRPORT INDIRECT REACH\n";

        cout << "\n type 'q' to quit, 'r' to return\n";
        cout << "==================================================\n";
        getline(cin, option);
        if (option == "1")
            exit = generalSearchMenu();
        else if (option == "2")
            flightsAvailable();
        else if (option == "3")
            airlinesAvailable();
        else if (option == "4")
            exit = directSearch();
        else if (option == "5")
            exit = indirectSearch();
        else if (option == "r") return false;
        else if (option == "q") return true;
        else cout << "Invalid input\n";
    }
    return true;
}

bool MenuInfo::generalSearchMenu(){
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
        if (option == "1") airportByCode();
        else if (option == "2") airportByName();
        else if (option == "3") airportByCity();
        else if (option == "4") airportByCountry();
        else if (option == "5") airportByLocation();
        else if (option == "r") return false;
        else if (option == "q") return true;
        else cout << "Invalid input\n";
    }
}

bool MenuInfo::directSearch(){
    string option;
    while (true) {
        cout << "-> DIRECT CONNECTIONS\n\n";
        cout << "1 - AIRPORTS AVAILABLE\n";
        cout << "2 - DESTINATIONS AVAILABLE\n";
        cout << "3 - COUNTRIES AVAILABLE\n";

        cout << "\n type 'q' to quit, 'r' to return\n";
        cout << "==================================================\n";
        getline(cin, option);
        if (option == "1") directAirportsAvailable();
        else if (option == "2") directDestinationsAvailable();
        else if (option == "3") directCountriesAvailable();
        else if (option == "r") return false;
        else if (option == "q") return true;
        else cout << "Invalid input\n";
    }
}

bool MenuInfo::indirectSearch(){
    string option, stopovers;
    int maxDist;
    while (true) {
        bool inputing = true;
        cout << "-> INDIRECT CONNECTIONS\n\n";
        cout << "1 - AIRPORTS AVAILABLE\n";
        cout << "2 - DESTINATIONS AVAILABLE\n";
        cout << "3 - COUNTRIES AVAILABLE\n";

        cout << "\n type 'q' to quit, 'r' to return\n";
        cout << "==================================================\n";
        getline(cin, option);
        if (option == "r") return false;
        else if (option == "q") return true;
        else if (option == "1" || option == "2" || option == "3"){
            while (inputing){
                cout << "Max Flights:";
                getline(cin, stopovers);
                inputing = false;
                try{
                    maxDist = stoi(stopovers);
                }
                catch (invalid_argument){
                    cout << "invalid input\n\n";
                    inputing = true;
                }
                if (maxDist <= 0){
                    inputing = true;
                    cout << "invalid input\n";
                }
            }
            if (option == "1") indirectAirportsAvailable(maxDist);
            else if (option == "2") indirectDestinationsAvailable(maxDist);
            else if (option == "3") indirectCountriesAvailable(maxDist);
        }
        else cout << "Invalid input\n";
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

void MenuInfo::airportByCode() {
    string code;
    cout << "Airport Code: ";
    getline(cin, code);
    Airport airport = Airport(code);
    auto verify = management.getAirportNode().find(airport);
    if (verify != management.getAirportNode().end())
        printAirportInfo(verify->first);
    else cout << "No airport with such code\n";
}

void MenuInfo::airportByName() {
    bool found = false;
    string name;
    cout << "Airport Name: ";
    getline(cin, name);
    for (const auto& airport : management.getAirportNode()){
        if (airport.first.getName() == name){
            printAirportInfo(airport.first);
            found = true;
            break;
        }
    }
    if(!found) cout << "No airport with such name\n";
}

void MenuInfo::airportByCity() {
    string city;
    cout << "City: ";
    getline(cin, city);
    auto verify = management.getCityAirports().find(city);
    if (verify != management.getCityAirports().end())
        for (const Airport* a : verify->second)
            printAirportInfo(*a);
    else cout << "City doesn't have airports\n";
}

void MenuInfo::airportByCountry() {
    bool found = false;
    string country;
    cout << "Country: ";
    getline(cin, country);
    for (const auto& airport : management.getAirportNode()){
        if (airport.first.getCountry() == country){
            printAirportInfo(airport.first);
            found = true;
        }
    }
    if(!found) cout << "Country doesn't have airports\n";
}

void MenuInfo::airportByLocation() {
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
                if (minLat<-90 || minLat>90){
                    cout << "Invalid Latitude Range: [-90.0,90.0]";
                    continue;
                }
            }
            catch (invalid_argument){
                cout << "Invalid Input\n";
                continue;
            }
        }
        if (i == 1){
            try{
                maxLat = stof(stringInput);
                if (maxLat<-90 || maxLat>90){
                    cout << "Invalid Latitude Range: [-90.0,90.0]";
                    continue;
                }
                if (maxLat<minLat){
                    cout << "Max Latitude can't be inferior to Min Latitude";
                    continue;
                }
            }
            catch (invalid_argument){
                cout << "Invalid Input\n";
                continue;
            }
        }
        if (i == 2){
            try{
                minLon = stof(stringInput);
                if (minLon<-180 || minLon>180){
                    cout << "Invalid Longitude Range: [-180.0,180.0]";
                    continue;
                }
            }
            catch (invalid_argument){
                cout << "Invalid Input\n";
                continue;
            }
        }
        if (i == 3){
            try{
                maxLon = stof(stringInput);
                if (maxLon<-180 || maxLon>180){
                    cout << "Invalid Longitude Range: [-180.0,180.0]";
                    continue;
                }
                if (maxLon<minLon){
                    cout << "Max Longitude can't be inferior to Min Longitude";
                    continue;
                }
            }
            catch (invalid_argument){
                cout << "Invalid Input\n";
                continue;
            }
        }
        i++;
    }
    for (const auto& airport : management.getAirportNode()){
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
    auto airport_node = management.getAirportNode().find(Airport(code));
    if (airport_node == management.getAirportNode().end()){
        cout << "No airport with such code\n";
        return;
    }
    int graph_pos = airport_node->second;
    auto nodes = flights.getNodes();
    auto node = nodes[graph_pos];
    for (auto it = node.adj.begin(); it != node.adj.end();it++) counter++;
    cout << "Airport " << code << " has " << counter << " flights\n";
}

void MenuInfo::airlinesAvailable() {
    auto flights = management.getFlights();
    int counter = 0;
    unordered_set<string> airlines;
    string code;
    cout << "Airport Code: ";
    getline(cin, code);
    auto airport_node = management.getAirportNode().find(Airport(code));
    if (airport_node == management.getAirportNode().end()){
        cout << "No airport with such code\n";
        return;
    }
    int graph_pos = airport_node->second;
    auto nodes = flights.getNodes();
    auto node = nodes[graph_pos];
    for (auto & it : node.adj)
        if (airlines.insert(it.airline->getCode()).second)
            counter++;
    cout << "Airport " << code << " has " << counter << " airlines\n";
}

void MenuInfo::directAirportsAvailable(){
    auto flights = management.getFlights();
    int counter = 0;
    unordered_set<string> airports;
    string code;
    cout << "Airport Code: ";
    getline(cin, code);
    auto airport_node = management.getAirportNode().find(Airport(code));
    if (airport_node == management.getAirportNode().end()){
        cout << "No airport with such code\n";
        return;
    }
    int graph_pos = airport_node->second;
    auto nodes = flights.getNodes();
    auto node = nodes[graph_pos];
    for (auto & it : node.adj){
        auto airport = management.getNodeAirport().find(it.dest);
        if (airports.insert(airport->second->getCode()).second)
            counter++;
    }
    cout << "Airport " << code << " can directly reach " << counter << " airports\n";
}

void MenuInfo::directDestinationsAvailable(){
    auto flights = management.getFlights();
    int counter = 0;
    unordered_set<string> destinations;
    string code;
    cout << "Airport Code: ";
    getline(cin, code);
    auto airport_node = management.getAirportNode().find(Airport(code));
    if (airport_node == management.getAirportNode().end()){
        cout << "No airport with such code\n";
        return;
    }
    int graph_pos = airport_node->second;
    auto nodes = flights.getNodes();
    auto node = nodes[graph_pos];
    for (auto & it : node.adj){
        auto airport = management.getNodeAirport().find(it.dest);
        if (destinations.find(airport->second->getCity()) == destinations.end()){
            destinations.insert(airport->second->getCity());
            counter++;
        }
    }
    cout << "Airport " << code << " can directly reach " << counter << " destinations\n";
}

void MenuInfo::directCountriesAvailable(){
    auto flights = management.getFlights();
    int counter = 0;
    unordered_set<string> countries;
    string code;
    cout << "Airport Code: ";
    getline(cin, code);
    auto airport_node = management.getAirportNode().find(Airport(code));
    if (airport_node == management.getAirportNode().end()){
        cout << "No airport with such code\n";
        return;
    }
    int graph_pos = airport_node->second;
    auto nodes = flights.getNodes();
    auto node = nodes[graph_pos];
    for (auto & it : node.adj){
        auto airport = management.getNodeAirport().find(it.dest);
        if (countries.insert(airport->second->getCountry()).second)
            counter++;
    }
    cout << "Airport " << code << " can directly reach " << counter << " countries\n";
}

void MenuInfo::indirectAirportsAvailable(int maxDist) {
    auto flights = management.getFlights();
    int counter = 0;
    unordered_set<string> airports;
    string code;
    cout << "Airport Code: ";
    getline(cin, code);
    auto airport_node = management.getAirportNode().find(Airport(code));
    if (airport_node == management.getAirportNode().end()){
        cout << "No airport with such code\n";
        return;
    }
    int graph_pos = airport_node->second;
    flights.bfs(queue<int>({graph_pos}), airports);
    auto nodes = flights.getNodes();
    for (int i=1; i<=nodes.size(); i++){
        if (nodes[i].dist <= maxDist && nodes[i].dist > 0){
            auto airport = management.getNodeAirport().find(i);
            if (airports.insert(airport->second->getCode()).second)
                counter++;
        }
    }
    cout << "Airport " << code << " can reach " << counter << " airports with " << maxDist << " flights\n";
}

void MenuInfo::indirectDestinationsAvailable(int maxDist) {
    auto flights = management.getFlights();
    int counter = 0;
    unordered_set<string> airports;
    string code;
    cout << "Airport Code: ";
    getline(cin, code);
    auto airport_node = management.getAirportNode().find(Airport(code));
    if (airport_node == management.getAirportNode().end()){
        cout << "No airport with such code\n";
        return;
    }
    int graph_pos = airport_node->second;
    queue<int> initial; initial.push(graph_pos);
    flights.bfs(initial, airports);
    auto nodes = flights.getNodes();
    for (int i=1; i<=nodes.size(); i++){
        if (nodes[i].dist <= maxDist && nodes[i].dist > 0){
            auto airport = management.getNodeAirport().find(i);
            if (airports.insert(airport->second->getCity()).second)
                counter++;
        }
    }
    cout << "Airport " << code << " can reach " << counter << " destinations with " << maxDist << " flights\n";
}

void MenuInfo::indirectCountriesAvailable(int maxDist) {
    auto flights = management.getFlights();
    int counter = 0;
    unordered_set<string> airports;
    string code;
    cout << "Airport Code: ";
    getline(cin, code);
    auto airport_node = management.getAirportNode().find(Airport(code));
    if (airport_node == management.getAirportNode().end()){
        cout << "No airport with such code\n";
        return;
    }
    int graph_pos = airport_node->second;
    queue<int> initial; initial.push(graph_pos);
    flights.bfs(initial, airports);
    auto nodes = flights.getNodes();
    for (int i=1; i<=nodes.size(); i++){
        if (nodes[i].dist <= maxDist && nodes[i].dist > 0){
            auto airport = management.getNodeAirport().find(i);
            if (airports.insert(airport->second->getCountry()).second)
                counter++;
        }
    }
    cout << "Airport " << code << " can reach " << counter << " countries with " << maxDist << " flights\n";
}