#include "MenuTravel.h"
#include <cmath>

MenuTravel::MenuTravel(const FlightManagement &management): Menu(management) {}

bool MenuTravel::start() {
    cout << "##########\n";
    cout << "# TRAVEL #\n";
    cout << "##########\n\n";

    cout << "-> FROM:\n";
    list<const Airport*> departure = getAirports();
    cout << "-> TO:\n";
    list<const Airport*> arrival = getAirports();

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
            /*
             * verificar se o input é um aeroporto quer seja fornecido o código quer seja fornecido o nome
             * mudar o operator==
             */
        } else if (option == "2"){
            cout << "City: ";
            getline(cin, criteria);
            auto it = management.getCityAirports().find(criteria);
            if (it != management.getCityAirports().end())
                return (*it).second;
            else cout << "Airport not found!\n\n";
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
        }
    }
}
