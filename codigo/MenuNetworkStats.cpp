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
        cout << "4 - STRONGLY CONNECTED COMPONENTS\n";
        cout << "5 - NODES & EDGES\n";
        cout << "6 - TOP K BUSIEST AIRPORTS\n";
        cout << "7 - TOTAL FLIGHTS PER CITY\n";
        cout << "8 - TOTAL FLIGHTS PER AIRLINE\n";

        cout << "\n type 'q' to quit, 'r' to return\n";
        cout << "==================================================\n";
        getline(cin, option);
        if (option == "1")
            globalArticulationPoints();
        else if (option == "2")
            globalDiameter();
        else if (option == "3")
            globalConnectedComponents();
        else if (option == "4")
            globalSCC();
        else if (option == "5")
            nodesAndEdges();
        else if (option == "6")
            topKBusiestAirports();
        else if (option == "7")
            flightPerCity();
        else if (option == "8")
            flightPerAirline();
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
        cout << "4 - STRONGLY CONNECTED COMPONENTS\n";

        cout << "\n type 'q' to quit, 'r' to return\n";
        cout << "==================================================\n";
        getline(cin, option);
        if (option == "r") return false;
        else if (option == "q") return true;
        else if (option == "1" || option == "2" || option == "3" || option == "4"){
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
                if (option == "4")
                    continentalSCC(selected);
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
        cout << "4 - STRONGLY CONNECTED COMPONENTS\n";

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
        else if (option == "4"){
            cout << "Country: ";
            getline(cin, country);
            countrySCC(country);
        }
        else cout << "Invalid input\n";
    }
}

void MenuNetworkStats::nodesAndEdges() {
    Graph graph = management.getFlights();
    auto nodes = graph.getNodes();
    int numNodes = nodes.size()-1;
    int numEdges = 0;
    for(auto node:nodes){
        numEdges += node.adj.size();
    }
    cout << "Number of airports: " << numNodes << "\n";
    cout << "Number of flights: " << numEdges << "\n";

}

void MenuNetworkStats::topKBusiestAirports() {
    string str_k;
    int k;
    bool trial = true;
    Graph graph = management.getFlights();
    auto map = management.getNodeAirport();
    vector<pair<int,int>> busiestAirports = graph.topBusiestAirports();
    while(trial) {
        try {
            cout << "Top K airports: ";
            getline(cin, str_k);
            k = stoi(str_k);
            if(k>=graph.getNodes().size() || k<1)
                throw std::invalid_argument("");
            trial = false;
        }
        catch (...) {
            cout << "Error: invalid number\n";
            continue;
        }
    }

    for (int num=1;num<=k;num++){
        cout << num << ". " << map[busiestAirports[num-1].first]->getName()
        << "(" << map[busiestAirports[num-1].first]->getCode() << ") -> "
        << busiestAirports[num-1].second << " fights in/out\n";
    }
}

void MenuNetworkStats::globalArticulationPoints() {
    Graph graph = management.getFlights();
    auto map = management.getNodeAirport();
    vector<int> aps = graph.getGlobalArticulationPoints();
    cout << "Number of global articulation points: " << aps.size() << "\n";
    for (int i : aps) {
        cout << map[i]->getName() << "(" << map[i]->getCode() << ")\n";
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
    pair<int,vector<pair<int,int>>> pair = graph.getGlobalDiameter();
    int diameter = pair.first;
    cout << "Global diameter: " << diameter << "\n";
    for(auto source_dest:pair.second){
        auto source = management.getNodeAirport().find(source_dest.first);
        auto dest = management.getNodeAirport().find(source_dest.second);
        cout << "\t" << source->second->getName() << "(" << source->second->getCode() << ") -> " << dest->second->getName() << "("<< dest->second->getCode() << ")\n";
    }
}

void MenuNetworkStats::continentalDiameter(int option) {
    Graph graph = management.getFlights();
    auto map = management.getNodeAirport();
    vector<string> continents = {"Africa", "Asia", "Europe", "North America", "Oceania", "South America"};
    pair<int,vector<pair<int,int>>> pair = graph.getContinentalDiameter(map, getCountriesOf(continents[option]));
    int diameter = pair.first;
    cout << "Global diameter: " << diameter << "\n";
    for(auto source_dest:pair.second){
        auto source = management.getNodeAirport().find(source_dest.first);
        auto dest = management.getNodeAirport().find(source_dest.second);
        cout << "\t" << source->second->getName() << "(" << source->second->getCode() << ") -> " << dest->second->getName() << "("<< dest->second->getCode() << ")\n";
    }
}

void MenuNetworkStats::countryDiameter(string country) {
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
    pair<int,vector<pair<int,int>>> pair = graph.getCountryDiameter(map, country);
    int diameter = pair.first;
    cout << "Global diameter: " << diameter << "\n";
    for(auto source_dest:pair.second){
        auto source = management.getNodeAirport().find(source_dest.first);
        auto dest = management.getNodeAirport().find(source_dest.second);
        cout << "\t" << source->second->getName() << "(" << source->second->getCode() << ") -> " << dest->second->getName() << "("<< dest->second->getCode() << ")\n";
    }
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
    int cc = graph.getContinentalConnectedComponents(map, getCountriesOf(continents[option]));
    cout << "Connected Components in " << continents[option] << ": " << cc << "\n";
}

void MenuNetworkStats::countryConnectedComponents(string country) {
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

void MenuNetworkStats::globalSCC() {
    Graph graph = management.getFlights();
    list<list<int>> globalConnectedComponents = graph.getGlobalSCC();
    cout << "Global Strongly Connected Components: " << globalConnectedComponents.size() << "\n";
}

void MenuNetworkStats::continentalSCC(int option) {
    Graph graph = management.getFlights();
    auto map = management.getNodeAirport();
    vector<string> continents = {"Africa", "Asia", "Europe", "North America", "Oceania", "South America"};
    list<list<int>> scc = graph.getContinentalSCC(map, getCountriesOf(continents[option]));
    cout << "Strongly Connected Components in " << continents[option] << ": " << scc.size() << "\n";
}

void MenuNetworkStats::countrySCC(string country) {
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
    list<list<int>> scc = graph.getCountrySCC(map, country);
    cout << "Strongly Connected Components in " << country << ": " << scc.size() << "\n";
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

void MenuNetworkStats::flightPerCity(){
    Graph graph = management.getFlights();
    auto airports = management.getNodeAirport();
    vector<pair<string, int>> flights_city = graph.getFlightsPerCity(airports);
    for(auto pair:flights_city){
        cout << pair.first << ": " << pair.second << " flights in/out of the city\n";
    }
}

void MenuNetworkStats::flightPerAirline(){
    Graph graph = management.getFlights();
    vector<pair<const Airline*, int>> flights_airline = graph.getFlightsPerAirline();

    for(auto pair:flights_airline){
        cout << pair.first->getName() << "(" << pair.first->getCode() << "): " << pair.second << " flights\n";
    }
}
