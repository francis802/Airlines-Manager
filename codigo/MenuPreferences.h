#ifndef NETWORKMANAGER_MENUPREFERENCES_H
#define NETWORKMANAGER_MENUPREFERENCES_H


#include "Menu.h"

class MenuPreferences: public Menu{
public:
    explicit MenuPreferences(const FlightManagement &management);

    bool start();
};


#endif //NETWORKMANAGER_MENUPREFERENCES_H
