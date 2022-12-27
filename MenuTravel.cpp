#include "MenuTravel.h"
#include <cmath>

MenuTravel::MenuTravel(const FlightManagement &management): Menu(management) {}

bool MenuTravel::start() {
    cout << "##########\n";
    cout << "# TRAVEL #\n";
    cout << "##########\n\n";

    cout << "-> FROM:\n";
    list<const Airport*> departure = getAirports();
    while (departure.empty()){
        cout << "Airport not found!\n\n";
        departure = getAirports();
    }
    cout << "-> TO:\n";
    list<const Airport*> arrival = getAirports();
    while (arrival.empty()){
        cout << "Airport not found!\n\n";
        arrival = getAirports();
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

list<const Airport*> MenuTravel::getAirports() {
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
            if (it != management.getAirportNode().end())
                return {&((*it).first)};
            else{
                for (auto i : management.getAirportNode())
                    if (i.first.getName() == criteria)
                        return {&i.first};
            }

        } else if (option == "2"){
            cout << "City: ";
            getline(cin, criteria);
            auto it = management.getCityAirports().find(criteria);
            if (it != management.getCityAirports().end())
                return (*it).second;
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

            list<const Airport*> airports;

            for (auto i : management.getAirportNode()){
                if (haversine(i.first.getLatitude(), i.first.getLongitude(), lat, lon) < dist)
                    airports.push_back(&i.first);
            }
            return airports;
        } else cout << "invalid input\n\n";
    }
}
