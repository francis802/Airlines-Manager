#include "MenuTravel.h"

MenuTravel::MenuTravel(const FlightManagement &management): Menu(management) {}

bool MenuTravel::start() {
    cout << "##########\n";
    cout << "# TRAVEL #\n";
    cout << "##########\n\n";

    cout << "-> FROM:\n";
    list<Airport> departure = getAirports();
    cout << "-> TO:\n";
    list<Airport> arrival = getAirports();
}

list<Airport> MenuTravel::getAirports() {
    while (true){
        cout << "\t1 - AIRPORT\n";
        cout << "\t2 - CITY\n";
        cout << "\t3 - LOCATION\n\n";

        string option;
        getline(cin, option);
        if (option == "1"){
            
        } else if (option == "2"){

        } else if (option == "3"){

        }
    }
}
