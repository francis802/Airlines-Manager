#ifndef PROJECT_AED_MENU_H
#define PROJECT_AED_MENU_H

#include <string>
#include <vector>
#include "FlightManagement.h"
#include <iostream>

class Menu {
protected:
    FlightManagement management;

public:
    explicit Menu(const FlightManagement &management);
    void start();
};


#endif
