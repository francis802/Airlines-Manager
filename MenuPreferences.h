#ifndef NETWORKMANAGER_MENUPREFERENCES_H
#define NETWORKMANAGER_MENUPREFERENCES_H


#include "Menu.h"

class MenuPreferences: public Menu{
public:
    explicit MenuPreferences(const FlightManagement &management);

    bool start();
    unordered_set<string> readPreferences();
    void savePreferences(unordered_set<string> preferences);
};


#endif //NETWORKMANAGER_MENUPREFERENCES_H
