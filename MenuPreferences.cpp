#include "MenuPreferences.h"

MenuPreferences::MenuPreferences(const FlightManagement &management): Menu(management) {}

bool MenuPreferences::start() {
    while (true) {
        cout << "-> PREFERENCES\n\n";

        cout << "\n type 'q' to quit, 'r' to return\n";
        cout << "==================================================\n";
    }
}