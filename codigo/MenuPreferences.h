#ifndef NETWORKMANAGER_MENUPREFERENCES_H
#define NETWORKMANAGER_MENUPREFERENCES_H


#include "Menu.h"

/**
 * \brief Classe MenuPreferences
 *
 * Classe filha da classe Menu, utilizada para alterar e visualizar as preferências de companhias aéreas
 */
class MenuPreferences: public Menu{
public:
    /**
     * Construtor da classe MenuPreferences
     * @param management
     */
    explicit MenuPreferences(const FlightManagement &management);

    /**
     * Inicializa o menu de preferências. Interface gráfica que permite alterar as preferências do utilizador em relação às companhias aéreas.
     * @return false para continuar o programa, true para sair
     */
    bool start();
};


#endif //NETWORKMANAGER_MENUPREFERENCES_H
