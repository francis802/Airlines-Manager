#include "Menu.h"
#include "MenuTravel.h"
#include "MenuInfo.h"
#include "MenuPreferences.h"

Menu::Menu(const FlightManagement &management) : management(management) {}

void Menu::start() {
    bool exit = false;
    string option;
    while (!exit) {
        cout << "==================================================\n";
        cout << "1 - TRAVEL\n";
        cout << "2 - INFO AIRPORTS\n";
        cout << "3 - PREFERENCES\n";

        cout << "\n type 'q' to quit\n";
        cout << "==================================================\n";

        getline(cin, option);
        if (option == "1"){
            MenuTravel travel = MenuTravel(management);
            exit = travel.start();
        }
        else if (option == "2"){
            MenuInfo info = MenuInfo(management);
            exit = info.start();
        }
        else if (option == "3"){
            MenuPreferences preferences = MenuPreferences(management);
            exit = preferences.start();
        }
        else if (option == "q") break;
        else cout << "invalid input\n\n";
    }
}