#include "MenuNetworkStats.h"

MenuNetworkStats::MenuNetworkStats(const FlightManagement &management): Menu(management) {}

bool MenuNetworkStats::start() {
    bool exit = false;
    string option;
    while (!exit) {
        cout << "-> NETWORK STATS\n\n";
        cout << "1 - GLOBAL STATS\n";
        cout << "2 - CONTINENTAL STATS\n";
        cout << "3 - COUNTRY STATS\n";

        cout << "\n type 'q' to quit, 'r' to return\n";
        cout << "==================================================\n";
        getline(cin, option);
        if (option == "1")
            exit = globalStatsMenu();
        else if (option == "2")
            exit = continentalStatsMenu();
        else if (option == "3")
            exit = countryStatsMenu();
        else if (option == "r") return false;
        else if (option == "q") return true;
        else cout << "Invalid input\n";
    }
    return true;
}

bool MenuNetworkStats::globalStatsMenu() {
    string option;
    while (true) {
        cout << "-> GLOBAL STATS\n\n";
        cout << "1 - ARTICULATION POINTS\n";
        cout << "2 - DIAMETER\n";
        cout << "3 - CONNECTED COMPONENTS\n";

        cout << "\n type 'q' to quit, 'r' to return\n";
        cout << "==================================================\n";
        getline(cin, option);
        if (option == "1")
            globalArticulationPoints();
        if (option == "2")
            globalDiameter();
        if (option == "3")
            globalConnectedComponents();
        else if (option == "r") return false;
        else if (option == "q") return true;
        else cout << "Invalid input\n";
    }
}

bool MenuNetworkStats::continentalStatsMenu() {
    string option, continent;
    while (true) {
        cout << "-> CONTINENTAL STATS\n\n";
        cout << "1 - ARTICULATION POINTS\n";
        cout << "2 - DIAMETER\n";
        cout << "3 - CONNECTED COMPONENTS\n";

        cout << "\n type 'q' to quit, 'r' to return\n";
        cout << "==================================================\n";
        getline(cin, option);
        if (option == "r") return false;
        else if (option == "q") return true;
        else if (option == "1" || option == "2" || option == "3"){
            cout << "-> CHOOSE CONTINENT:\n\n";
            cout << "1 - Africa\n";
            cout << "2 - Asia\n";
            cout << "3 - Europe\n";
            cout << "4 - North America\n";
            cout << "5 - Oceania\n";
            cout << "6 - South America\n";

            getline(cin, continent);
            if (continent == "1" || continent == "2" || continent == "3" || continent == "4" || continent == "5" || continent == "6"){
                int selected = stoi(continent)-1;
                if (option == "1")
                    continentalArticulationPoints(selected);
                if (option == "2")
                    continentalDiameter(selected);
                if (option == "3")
                    continentalConnectedComponents(selected);
            }
            else cout << "Invalid input\n";
        }
        else cout << "Invalid input\n";
    }
}

bool MenuNetworkStats::countryStatsMenu() {
    string option, country;
    while (true) {
        cout << "-> COUNTRY STATS\n\n";
        cout << "1 - ARTICULATION POINTS\n";
        cout << "2 - DIAMETER\n";
        cout << "3 - CONNECTED COMPONENTS\n";

        cout << "\n type 'q' to quit, 'r' to return\n";
        cout << "==================================================\n";
        getline(cin, option);
        if (option == "r") return false;
        else if (option == "q") return true;
        else if (option == "1"){
            cout << "Country: ";
            getline(cin, country);
            countryArticulationPoints(country);
        }
        else if (option == "2"){
            cout << "Country: ";
            getline(cin, country);
            countryDiameter(country);
        }
        else if (option == "3"){
            cout << "Country: ";
            getline(cin, country);
            countryConnectedComponents(country);
        }
        else cout << "Invalid input\n";
    }
}

void MenuNetworkStats::globalArticulationPoints() {
    Graph graph = management.getFlights();
    auto map = management.getNodeAirport();
    vector<int> aps = graph.getGlobalArticulationPoints();
    cout << "Number of global articulation points: " << aps.size() << "\n";
    for (int i : aps) {
        cout << map[i]->getName() << "\n";
    }
}

void MenuNetworkStats::continentalArticulationPoints(int option) {
    Graph graph = management.getFlights();
    auto map = management.getNodeAirport();
    vector<string> continents = {"Africa", "Asia", "Europe", "North America", "Oceania", "South America"};
    vector<int> aps = graph.getContinentalArticulationPoints(map, getCountriesOf(continents[option]));
    cout << "Number of articulation points in " << continents[option] << ": " << aps.size() << "\n";
    for (int i : aps) {
        cout << map[i]->getName() << "\n";
    }
}

void MenuNetworkStats::countryArticulationPoints(string country) {
    bool found = false;
    Graph graph = management.getFlights();
    auto map = management.getNodeAirport();
    for (int i=1;i<map.size();i++){
        if (map[i]->getCountry() == country)
            found = true;
    }
    if (!found) {
        cout << "No country with such name\n";
        return;
    }
    vector<int> aps = graph.getCountryArticulationPoints(map,country);

    cout << "Number of articulation points in " << country << ": " << aps.size() << "\n";
    for (int i : aps) {
        cout << map[i]->getName() << "\n";
    }
}

void MenuNetworkStats::globalDiameter() {
    Graph graph = management.getFlights();
    int diameter = graph.getGlobalDiameter();
    cout << "Global diameter: " << diameter << "\n";
}

void MenuNetworkStats::continentalDiameter(int option) {
    Graph graph = management.getFlights();
    auto map = management.getNodeAirport();
    vector<string> continents = {"Africa", "Asia", "Europe", "North America", "Oceania", "South America"};
    int diameter = graph.getContinentalDiameter(map, getCountriesOf(continents[option]));
    cout << "Diameter in " << continents[option] << ": " << diameter << "\n";
}

void MenuNetworkStats::countryDiameter(std::string country) {
    bool found = false;
    Graph graph = management.getFlights();
    auto map = management.getNodeAirport();
    for (int i=1;i<map.size();i++){
        if (map[i]->getCountry() == country)
            found = true;
    }
    if (!found) {
        cout << "No country with such name\n";
        return;
    }
    int diameter = graph.getCountryDiameter(map, country);
    cout << "Diameter in " << country << ": " << diameter << "\n";
}

void MenuNetworkStats::globalConnectedComponents() {
    Graph graph = management.getFlights();
    int globalConnectedComponents = graph.getGlobalConnectedComponents();
    cout << "Global connected components: " << globalConnectedComponents << "\n";
}

void MenuNetworkStats::continentalConnectedComponents(int option) {
    Graph graph = management.getFlights();
    auto map = management.getNodeAirport();
    vector<string> continents = {"Africa", "Asia", "Europe", "North America", "Oceania", "South America"};
    int cc = graph.getContinentalDiameter(map, getCountriesOf(continents[option]));
    cout << "Connected Components in " << continents[option] << ": " << cc << "\n";
}

void MenuNetworkStats::countryConnectedComponents(std::string country) {
    bool found = false;
    Graph graph = management.getFlights();
    auto map = management.getNodeAirport();
    for (int i=1;i<map.size();i++){
        if (map[i]->getCountry() == country)
            found = true;
    }
    if (!found) {
        cout << "No country with such name\n";
        return;
    }
    int cc = graph.getCountryConnectedComponents(map, country);
    cout << "Connected Components in " << country << ": " << cc << "\n";
}

unordered_set<string> MenuNetworkStats::getCountriesOf(const string& continent) {
    unordered_map<string, unordered_set<string>> continents;
    continents.insert({
            {"Africa",{"Algeria", "Angola", "Benin", "Botswana", "Burkina Faso", "Burundi", "Cape Verde", "Cameroon",
                       "Central African Republic", "Chad", "Comoros", "Congo (Brazzaville)", "Congo (Kinshasa)",
                       "Cote d'Ivoire", "Djibouti", "Egypt",  "Equatorial Guinea", "Eritrea",
                       "Ethiopia", "Gabon", "Gambia", "Ghana", "Guinea", "Guinea-Bissau", "Kenya",
                       "Lesotho", "Liberia", "Libya", "Madagascar", "Malawi", "Mali", "Mauritania", "Mauritius",
                       "Morocco", "Mozambique", "Namibia", "Niger", "Nigeria", "Rwanda", "Sao Tome and Principe",
                       "Senegal", "Seychelles", "Sierra Leone", "Somalia", "South Africa", "South Sudan", "Sudan",
                       "Swaziland", "Tanzania", "Togo", "Tunisia", "Uganda", "Zambia", "Zimbabwe", "Mayotte", "Reunion",
                       "Western Sahara"}},
            {"Asia",{"Afghanistan", "Armenia", "Azerbaijan", "Bahrain", "Bangladesh", "Bhutan", "Brunei", "Burma", "Cambodia", "China",
                           "Georgia", "India", "Indonesia", "Iran", "Iraq", "Israel", "Japan", "Jordan", "Kazakhstan",
                           "Kuwait",   "Kyrgyzstan", "Laos", "Lebanon", "Malaysia", "Maldives", "Mongolia", "Nepal",
                           "Oman", "Pakistan", "Philippines", "Qatar", "Saudi Arabia",
                           "Singapore", "South Korea", "Sri Lanka",  "Taiwan", "Tajikistan", "Thailand", "East Timor",
                           "Turkey",  "Turkmenistan", "United Arab Emirates", "Uzbekistan", "Vietnam",  "Yemen", "Macau", "Korea", "Hong Kong"}},
            {"Europe",{"Albania", "Austria", "Belarus", "Belgium", "Bosnia and Herzegovina", "Bulgaria", "Croatia",
                            "Cyprus", "Czech Republic", "Denmark", "Estonia", "Finland", "France", "Germany", "Greece", "Hungary", "Iceland",
                            "Ireland", "Italy", "Latvia", "Lithuania", "Luxembourg", "Malta", "Macedonia",
                            "Moldova", "Monaco", "Montenegro", "Netherlands", "Norway", "Poland", "Portugal", "Romania", "Russia",
                            "Serbia", "Slovakia", "Slovenia", "Spain", "Sweden", "Switzerland", "Ukraine", "United Kingdom", "Faroe Islands", "Gibraltar",
                            "Guernsey", "Isle of Man", "Jersey"}},
            {"North America",{"Antigua and Barbuda", "Anguilla", "Bahamas", "Barbados", "Belize", "Bermuda", "Canada", "Costa Rica", "Cuba", "Dominica",
                              "Dominican Republic", "El Salvador", "Grenada", "Guatemala", "Haiti", "Honduras", "Jamaica", "Mexico",
                              "Nicaragua", "Panama", "Saint Kitts and Nevis", "Saint Lucia", "Saint Vincent and the Grenadines",
                              "Trinidad and Tobago", "United States", "British Virgin Islands", "Greenland", "Guadeloupe", "Martinique",
                              "Saint Pierre and Miquelon", "Turks and Caicos Islands", "Virgin Islands", "Puerto Rico", "Cayman Islands"}},
            {"South America",{"Argentina", "Aruba", "Bolivia", "Brazil", "Chile", "Colombia", "Ecuador", "Falkland Islands", "French Guiana",
                              "Guyana", "Paraguay", "Peru", "Suriname", "Uruguay", "Venezuela", "Netherlands Antilles"}},
            {"Oceania",{"Australia", "American Samoa", "Christmas Island", "Cocos (Keeling) Islands", "Cook Islands", "Fiji",
                             "French Polynesia", "Guam", "Kiribati", "Marshall Islands", "Micronesia", "Nauru", "New Caledonia",
                             "New Zealand", "Niue", "Norfolk Island", "Northern Mariana Islands", "Palau", "Papua New Guinea",
                             "Samoa", "Solomon Islands", "Tonga", "Tuvalu", "Vanuatu", "Wallis and Futuna"}}
    });
    return continents[continent];
}