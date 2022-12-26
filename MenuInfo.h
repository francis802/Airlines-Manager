#ifndef NETWORKMANAGER_MENUINFO_H
#define NETWORKMANAGER_MENUINFO_H


#include "Menu.h"

class MenuInfo: public Menu{
public:
    explicit MenuInfo(const FlightManagement &management);

    bool start();
};


#endif //NETWORKMANAGER_MENUINFO_H
