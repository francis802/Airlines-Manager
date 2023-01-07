#include "MenuNetworkStats.h"

MenuNetworkStats::MenuNetworkStats(const FlightManagement &management): Menu(management) {}

bool MenuNetworkStats::start() {
    bool exit = false;
    string option;
    while (!exit) {
        cout << "-> NETWORK STATS\n\n";
        cout << "1 - GLOBAL STATS\n";
        cout << "2 - COUNTRY STATS\n";

        cout << "\n type 'q' to quit, 'r' to return\n";
        cout << "==================================================\n";
        getline(cin, option);
        if (option == "1")
            exit = globalStatsMenu();
        if (option == "2")
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

bool MenuNetworkStats::countryStatsMenu() {
    string option;
    while (true) {
        cout << "-> COUNTRY STATS\n\n";
        cout << "1 - ARTICULATION POINTS\n";

        cout << "\n type 'q' to quit, 'r' to return\n";
        cout << "==================================================\n";
        getline(cin, option);
        if (option == "1")
            countryArticulationPoints();
        else if (option == "r") return false;
        else if (option == "q") return true;
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

void MenuNetworkStats::countryArticulationPoints() {
    bool found = false;
    string country;
    cout << "Country: ";
    getline(cin, country);
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

string MenuNetworkStats::get_continent(const string& country) {
    unordered_map<string, vector<string>> continents;
    continents.insert({
            {"Africa",{"Algeria", "Angola", "Benin", "Botswana", "Burkina Faso", "Burundi", "Cape Verde", "Cameroon",
                       "Central African Republic", "Chad", "Comoros", "Congo (Brazzaville)", "Congo (Kinshasa)",
                       "Cote d'Ivoire", "Djibouti", "Egypt",  "Equatorial Guinea", "Eritrea",
                       "Ethiopia", "Gabon", "Gambia", "Ghana", "Guinea", "Guinea-Bissau", "Ivory Coast", "Kenya",
                       "Lesotho", "Liberia", "Libya", "Madagascar", "Malawi", "Mali", "Mauritania", "Mauritius",
                       "Morocco", "Mozambique", "Namibia", "Niger", "Nigeria", "Rwanda", "Sao Tome and Principe",
                       "Senegal", "Seychelles", "Sierra Leone", "Somalia", "South Africa", "South Sudan", "Sudan",
                       "Swaziland", "Tanzania", "Togo", "Tunisia", "Uganda", "Zambia", "Zimbabwe", "Mayotte", "Reunion",
                       "Western Sahara"}},
            {"Asia",{"Afghanistan", "Armenia", "Azerbaijan", "Bahrain", "Bangladesh", "Bhutan", "Brunei", "Burma", "Cambodia", "China",
                           "Georgia", "India", "Indonesia", "Iran", "Iraq", "Israel", "Japan", "Jordan", "Kazakhstan",
                           "Kuwait",   "Kyrgyzstan", "Laos", "Lebanon", "Malaysia", "Maldives", "Mongolia", "Nepal",
                           "North Korea", "Oman", "Pakistan", "Palestine", "Philippines", "Qatar", "Saudi Arabia",
                           "Singapore", "South Korea", "Sri Lanka", "Syria",  "Taiwan", "Tajikistan", "Thailand", "East Timor",
                           "Turkey",  "Turkmenistan", "United Arab Emirates", "Uzbekistan", "Vietnam",  "Yemen", "Macau"}},
            {"Europe",{"Albania", "Andorra", "Austria", "Belarus", "Belgium", "Bosnia and Herzegovina", "Bulgaria", "Croatia",
                            "Cyprus", "Czech Republic", "Denmark", "Estonia", "Finland", "France", "Germany", "Greece", "Hungary", "Iceland",
                            "Ireland", "Italy", "Kosovo", "Latvia", "Liechtenstein", "Lithuania", "Luxembourg", "Malta",
                            "Moldova", "Monaco", "Montenegro", "Netherlands", "Norway", "Poland", "Portugal", "Romania", "Russia", "San Marino",
                            "Serbia", "Slovakia", "Slovenia", "Spain", "Sweden", "Switzerland", "Ukraine", "United Kingdom", "Faroe Islands", "Gibraltar",
                            "Guernsey", "Isle of Man", "Jersey"}},
            {"North America",{"Antigua and Barbuda", "Anguilla", "Bahamas", "Barbados", "Belize", "Bermuda", "Canada", "Costa Rica", "Cuba", "Dominica",
                              "Dominican Republic", "El Salvador", "Grenada", "Guatemala", "Haiti", "Honduras", "Jamaica", "Mexico",
                              "Nicaragua", "Panama", "Saint Kitts and Nevis", "Saint Lucia", "Saint Vincent and the Grenadines",
                              "Trinidad and Tobago", "United States", "British Virgin Islands", "Greenland", "Guadeloupe", "Martinique", "Montserrat",
                              "Saint Pierre and Miquelon", "Turks and Caicos Islands"}},
            {"South America",{"Argentina", "Aruba", "Bolivia", "Brazil", "Chile", "Colombia", "Ecuador", "Falkland Islands", "French Guiana",
                              "Guyana", "Paraguay", "Peru", "Suriname", "Uruguay", "Venezuela", "Netherlands Antilles"}},
            {"Oceania",{"Australia", "American Samoa", "Christmas Island", "Cocos (Keeling) Islands", "Cook Islands", "Fiji",
                             "French Polynesia", "Guam", "Kiribati", "Marshall Islands", "Micronesia", "Nauru", "New Caledonia",
                             "New Zealand", "Niue", "Norfolk Island", "Northern Mariana Islands", "Palau", "Papua New Guinea",
                             "Pitcairn", "Samoa", "Solomon Islands", "Tonga", "Tuvalu", "Vanuatu", "Wallis and Futuna",
                             "Pitcairn Islands"}}
    });
    return "";
}