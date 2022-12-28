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
    flights.bfs(departure);
    /*
     * only shows 1 path per distance
     */
    while (!arrival.empty()){
        list<int> paths;
        cout << flights.getNodes()[arrival.front()].dist << " flight(s) are needed\n";
        paths.push_front(arrival.front());
        int path = flights.getNodes()[arrival.front()].path;
        while (path != -1){
            paths.push_front(path);
            path = flights.getNodes()[path].path;
        }
        int num_flights = 1;
        for (int i : paths){
            cout << management.getNodeAirport().find(i)->second->getName() << endl;
            if (num_flights < paths.size())
                cout << "  ✈️ " << num_flights++ << endl;
        }
        cout << endl;
        arrival.pop();
    }

    return false;
}

double MenuTravel::haversine(double lat1, double lon1, double lat2, double lon2)
{
    // distance between latitudes
    // and longitudes
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
