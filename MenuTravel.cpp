#include "MenuTravel.h"
#include <cmath>
#include <queue>

MenuTravel::MenuTravel(const FlightManagement &management): Menu(management) {}

bool MenuTravel::start() {
    cout << "##########\n";
    cout << "# TRAVEL #\n";
    cout << "##########\n\n";

    cout << "-> FROM:\n";
    queue<int> departure = getAirports();
    while (departure.empty()) {
        cout << "Airport not found!\n\n";
        departure = getAirports();
    }

    cout << "-> TO:\n";
    queue<int> arrival = getAirports();
    while (arrival.empty()) {
        cout << "Airport not found!\n\n";
        arrival = getAirports();
    }

    Graph &flights = management.getFlights();
    unordered_set<string> preferences = management.readPreferences();
    flights.bfs(departure, preferences);

    list<int> min_arrival;
    int num_flights = INT32_MAX;
    while (!arrival.empty()){
        int dist = flights.getNodes()[arrival.front()].dist;
        if (dist < num_flights && dist != -1)
            num_flights = dist;
        min_arrival.push_back(arrival.front());
        arrival.pop();
    }

    if (num_flights == INT32_MAX){
        cout << "Not possible to reach destination with current preferences\n";
        return false;
    }
    cout << num_flights << " flight(s) are needed\n";

    for (auto it = min_arrival.begin(); it != min_arrival.end(); ){
        if (flights.getNodes()[*it].dist > num_flights)
            it = min_arrival.erase(it);
        else it++;
    }

    for(int airport : min_arrival){
        vector<int> paths = flights.getNodes()[airport].path;
        for (int path : paths){
            getPath({path, airport});
        }
    }

    return false;
}

void MenuTravel::getPath(list<int> current_path){
    Graph &flights = management.getFlights();
    vector<int> path = flights.getNodes()[current_path.front()].path;
    if (path.empty()){
        int num_flights = 1;
        for (int i : current_path){
            const Airport* airport = management.getNodeAirport().find(i)->second;
            cout << airport->getCode() << " " << airport->getName() << endl;
            if (num_flights < current_path.size())
                cout << "  ✈️ " << num_flights++ << endl;
        }
        cout << endl;
        return;
    }
    for (int i : path){
        list<int> next_path = current_path;
        next_path.push_front(i);
        getPath(next_path);
    }
}

double MenuTravel::haversine(double lat1, double lon1, double lat2, double lon2)
{
    // distance between latitudes and longitudes
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formulae
    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

queue<int> MenuTravel::getAirports() {
    while (true){
        cout << "\t1 - AIRPORT\n";
        cout << "\t2 - CITY\n";
        cout << "\t3 - LOCATION\n\n";

        string option, criteria;
        getline(cin, option);
        if (option == "1"){
            cout << "Airport: ";
            getline(cin, criteria);
            auto it = management.getAirportNode().find(Airport(criteria));
            if (it != management.getAirportNode().end()) {
                queue<int> q({(*it).second});
                return q;
            }
            else{
                for (auto i : management.getAirportNode())
                    if (i.first.getName() == criteria) {
                        queue<int> q({i.second});
                        return q;
                    }
                return {};
            }

        } else if (option == "2"){
            cout << "City: ";
            getline(cin, criteria);
            auto it = management.getCityAirports().find(criteria);
            if (it != management.getCityAirports().end()) {
                queue<int> q;
                for (const Airport* a : (*it).second)
                    q.push(management.getAirportNode().find(*a)->second);
                return q;
            }
            else return {};
        } else if (option == "3"){
            string latitude, longitude, distance;
            cout << "Latitude: ";
            getline(cin, latitude);
            cout << "Longitude: ";
            getline(cin, longitude);
            cout << "Max Distance: ";
            getline(cin, distance);

            double lat = stod(latitude);
            double lon = stod(longitude);
            double dist = stod(distance);

            queue<int> airports;

            for (auto i : management.getAirportNode()){
                if (haversine(i.first.getLatitude(), i.first.getLongitude(), lat, lon) < dist)
                    airports.push(i.second);
            }
            return airports;
        } else cout << "invalid input\n\n";
    }
}
