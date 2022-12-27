#include <fstream>
#include "MenuPreferences.h"

MenuPreferences::MenuPreferences(const FlightManagement &management): Menu(management) {}

bool MenuPreferences::start() {
    unordered_set<string> preferences = readPreferences();
    while (true) {
        cout << "-> PREFERENCES\n\n";
        cout << "\t1 - View Whitelist\n";
        cout << "\t2 - Add to Whitelist\n";
        cout << "\t3 - Remove from Whitelist\n";

        cout << "\n type 'q' to quit, 'r' to return\n";
        cout << "==================================================\n";

        string option;
        getline(cin, option);
        if (option == "1"){
            for (string s : preferences)
                cout << s << endl;
        } else if (option == "2"){
            cout << "leave blank to stop\n";
            string airline;
            while (true){
                cout << "Airline: ";
                getline(cin, airline);
                if (airline == "")
                    break;
                if (management.getAirlines().find(airline) == management.getAirlines().end())
                    cout << "Airline not found\n";
                else {
                    auto verify = preferences.insert(airline);
                    if (!verify.second)
                        cout << "airline is already in the whitelist\n";
                }
            }
        } else if (option == "3"){
            string airline;
            cout << "Airline: ";
            getline(cin, airline);
            auto verify = preferences.find(airline);
            if (verify != preferences.end())
                preferences.erase(verify);
        } else if (option == "q") {
            savePreferences(preferences);
            return true;
        }else if (option == "r") {
            savePreferences(preferences);
            return false;
        }
        else cout << "invalid input\n\n";
    }
}

void MenuPreferences::savePreferences(unordered_set<string> preferences) {
    ofstream out("../preferences");
    for (string s : preferences)
        out << s << endl;
}

unordered_set<string> MenuPreferences::readPreferences() {
    ifstream in("../preferences");
    string line;
    unordered_set<string> preferences;
    while (getline(in, line)){
        preferences.insert(line);
    }
    return preferences;
}