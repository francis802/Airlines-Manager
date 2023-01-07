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

        cout << "\n type 'q' to quit, 'r' to return\n";
        cout << "==================================================\n";
        getline(cin, option);
        if (option == "1")
            globalArticulationPoints();
        else if (option == "r") return false;
        else if (option == "q") return true;
        else cout << "Invalid input\n";
    }
}

bool MenuNetworkStats::continentalStatsMenu() {
    string option;
    while (true) {
        cout << "-> CONTINENTAL STATS\n\n";
        cout << "1 - ARTICULATION POINTS\n";

        cout << "\n type 'q' to quit, 'r' to return\n";
        cout << "==================================================\n";
        getline(cin, option);
        if (option == "r") return false;
        else if (option == "q") return true;
        else if (option == "1")
            continentalArticulationPoints("Africa");
        else cout << "Invalid input\n";
    }
}

bool MenuNetworkStats::countryStatsMenu() {
    string option, country;
    while (true) {
        cout << "-> COUNTRY STATS\n\n";
        cout << "1 - ARTICULATION POINTS\n";

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

void MenuNetworkStats::continentalArticulationPoints(string continent) {
    /*
    Graph graph = management.getFlights();
    auto map = management.getNodeAirport();
    vector<int> aps = graph.getGlobalArticulationPoints();
    cout << "Number of global articulation points: " << aps.size() << "\n";
    for (int i : aps) {
        cout << map[i]->getName() << "\n";
    }
     */
    int total = getCountriesOf("Africa").size() + getCountriesOf("Asia").size()
            + getCountriesOf("Oceania").size() + getCountriesOf("North America").size()
            + getCountriesOf("South America").size() + getCountriesOf("Europe").size();

    cout << "Total Countries: " << total << '\n';
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