#ifndef NETWORKMANAGER_MENUNETWORKSTATS_H
#define NETWORKMANAGER_MENUNETWORKSTATS_H

#include "Menu.h"
#include <unordered_map>
#include <vector>

/**
 * \brief Classe MenuNetworkStatus
 *
 * Classe filha da classe Menu, utilizada para visualizar estatísticas da rede de voos
 */
class MenuNetworkStats: public Menu {
public:
    /**
     * Construtor da classe MenuNetworkStats
     * @param management
     */
    explicit MenuNetworkStats(const FlightManagement& management);

    /**
     * Inicializa o menu de estatísticas. Interface gráfica para escolha do alcance da estatística.
     * @return false para continuar o programa, true para sair
     */
    bool start();

    /**
     * Menu de estatísticas globais. Interface gráfica para escolha do tipo de estatística pretendida.
     * @return false para continuar o programa, true para sair
     */
    bool globalStatsMenu();

    /**
     * Menu de estatísticas continentais. Interface gráfica para escolha do tipo de estatística pretendida.
     * @return false para continuar o programa, true para sair
     */
    bool continentalStatsMenu();

    /**
     * Menu de estatísticas por país. Interface gráfica para escolha do tipo de estatística pretendida.
     * @return false para continuar o programa, true para sair
     */
    bool countryStatsMenu();

    /**
     * Função responsável por chamar o método da classe Graph para calcular os pontos de articulação e imprimir os resultados.
     */
    void globalArticulationPoints();

    /**
     * Função responsável por chamar o método da classe Graph para calcular os pontos de articulação e imprimir os resultados.
     * @param option Continente a edetuar a pesquisa
     */
    void continentalArticulationPoints(int option);

    /**
     * Função responsável por chamar o método da classe Graph para calcular os pontos de articulação e imprimir os resultados.
     * @param country País a efetuar a pesquisa
     */
    void countryArticulationPoints(string country);

    /**
     * Função responsável por chamar o método da classe Graph para calcular o diâmetro e imprimir os resultados.
     */
    void globalDiameter();

    /**
     * Função responsável por chamar o método da classe Graph para calcular o diâmetro num determinado continente e imprimir os resultados.
     * @param option Número do continente
     */
    void continentalDiameter(int option);

    /**
     * Função responsável por chamar o método da classe Graph para calcular o diâmetro num determinado país e imprimir os resultados.
     * @param option País
     */
    void countryDiameter(string country);

    /**
     * Função responsável por chamar o método da classe Graph para calcular os componentes conexos e imprimir os resultados.
     */
    void globalConnectedComponents();

    /**
     * Função responsável por chamar o método da classe Graph para calcular os componentes conexos num determinado continente e imprimir os resultados.
     * @param option Número do continente
     */
    void continentalConnectedComponents(int option);

    /**
     * Função responsável por chamar o método da classe Graph para calcular os componentes conexos num determinado país e imprimir os resultados.
     * @param option País
     */
    void countryConnectedComponents(string country);

    /**
     * Função responsável por chamar o método da classe Graph para calcular os componentes fortemente conexos e imprimir os resultados.
     */
    void globalSCC();

    /**
     * Função responsável por chamar o método da classe Graph para calcular os componentes fortemente conexos num determinado continente e imprimir os resultados.
     * @param option Número do continente
     */
    void continentalSCC(int option);

    /**
     * Função responsável por chamar o método da classe Graph para calcular os componentes fortemente conexos num determinado país e imprimir os resultados.
     * @param option País
     */
    void countrySCC(string country);

    /**
     * @param continent Continente
     * @return Todos os países do continente
     */
    unordered_set<string> getCountriesOf(const string& continent);

    void nodesAndEdges();

    void topKBusiestAirports();
};

#endif //NETWORKMANAGER_MENUNETWORKSTATS_H
