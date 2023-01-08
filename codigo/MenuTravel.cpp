#include "MenuTravel.h"

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
        unordered_set<string> preferences = management.readPreferences();
        for (auto it = current_path.begin(); it != current_path.end(); it++){
            const Airport* airport = management.getNodeAirport().find(*it)->second;
            cout << airport->getCode() << " " << airport->getName() << endl;
            if (num_flights < current_path.size()) {
                cout << " " << num_flights++ << " ✈️ ";
                auto dep = it;
                auto arr = it;
                arr++;
                getAirlines(dep, arr, preferences);
                cout << endl;
            }
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

void MenuTravel::getAirlines(list<int>::iterator dep, list<int>::iterator arr, unordered_set<string> preferences) {
    auto nodes = management.getFlights().getNodes();
    for (auto e : nodes[*dep].adj){
        if (e.dest == *arr && (preferences.empty() || preferences.find(e.airline->getCode()) != preferences.end()))
            cout << e.airline->getCode() << " ";
    }
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
            double lat, lon, dist;
            lat = management.getNumbers("Latitude: ");
            while (lat < -90 || lat > 90){
                cout << "Invalid Latitude Range: [-90.0,90.0]\n";
                lat = management.getNumbers("Latitude: ");
            }
            lon = management.getNumbers("Longitude: ");
            while (lon < -180 || lon > 180){
                cout << "Invalid Longitude Range: [-180.0,180.0]";
                lon = management.getNumbers("Longitude: ");
            }
            dist = management.getNumbers("Max Distance: ");

            queue<int> airports;

            for (auto i : management.getAirportNode()){
                if (management.haversine(i.first.getLatitude(), i.first.getLongitude(), lat, lon) < dist)
                    airports.push(i.second);
            }
            return airports;
        } else cout << "invalid input\n\n";
    }
}
