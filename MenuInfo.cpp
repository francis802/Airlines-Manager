#include "MenuInfo.h"

MenuInfo::MenuInfo(const FlightManagement &management): Menu(management) {}

bool MenuInfo::start() {
    while (true) {
        cout << "-> INFO AIRPORTS\n\n";

        cout << "\n type 'q' to quit, 'r' to return\n";
        cout << "==================================================\n";
    }
}