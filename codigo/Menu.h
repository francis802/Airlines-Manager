#ifndef PROJECT_AED_MENU_H
#define PROJECT_AED_MENU_H

#include <string>
#include <vector>
#include "FlightManagement.h"
#include <iostream>

/**
 * Classe Menu
 *
 * Classe que atua como menu principal e parent para outros tipos de menu (Info, NetworkStats, Preferences, Travel)
 */
class Menu {
protected:
    FlightManagement management;

public:
    /**
     * Construtor da classe Menu
     * @param management
     */
    explicit Menu(const FlightManagement &management);

    /**
     * Inicializa o menu principal - interface do utilizador para aceder aos diferentes recursos do programa
     */
    void start();
};


#endif
