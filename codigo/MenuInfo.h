#ifndef NETWORKMANAGER_MENUINFO_H
#define NETWORKMANAGER_MENUINFO_H


#include "Menu.h"

/**
 * \brief Classe MenuInfo
 *
 * Classe filha da classe Menu, utilizada para visualizar informação acerca dos aeroportos
 */
class MenuInfo: public Menu{
public:
    /**
     * Construtor da classe MenuInfo
     * @param management
     */
    explicit MenuInfo(const FlightManagement &management);

    /**
     * Inicializa o menu de informação. Interface gráfica para escolha da informação pretendida.
     * @return false para continuar o programa, true para sair
     */
    bool start();

    /**
     * Menu de pesquisa geral. Interface gráfica para escolha da forma de pesquisar.
     * @return false para continuar o programa, true para sair
     */
    bool generalSearchMenu();

    /**
     * Menu de pesquisa direta. Interface gráfica para escolha do tipo de destino.
     * @return false para continuar o programa, true para sair
     */
    bool directSearch();

    /**
     * Menu de pesquisa indireta. Interface gráfica para escolha do tipo de destino.
     * @return false para continuar o programa, true para sair
     */
    bool indirectSearch();

    /**
     * \brief Pesquisa um aeroporto, dado um código
     *
     * Complexidade: O(1)
     */
    void airportByCode();

    /**
     * \brief Pesquisa um aeroporto, dado um nome
     *
     * Complexidade: O(n)
     */
    void airportByName();

    /**
     * \brief Pesquisa aeroportos, dada uma cidade
     *
     * Complexidade: O(n) em que n é o número de aeroportos encontrados
     */
    void airportByCity();

    /**
     * \brief Pesquisa aeroportos, dado um país
     *
     * Complexidade: O(n)
     */
    void airportByCountry();

    /**
     * \brief Pesquisa aeroportos, dadas coordenadas geográficas e uma distância máxima
     *
     * Complexidade: O(n*log(n))
     */
    void airportByLocation();

    /**
     * \brief Pesquisa os voos que saem de um determinado aeroporto
     *
     * Complexidade: O(n) em que n é o número de voos encontrados
     */
    void flightsAvailable();

    /**
     * \brief Pesquisa as companhias aéreas que têm voos a sair de um determinado aeroporto
     *
     * Complexidade: O(n) em que n é o número de voos a sair desse aeroporto
     */
    void airlinesAvailable();

    /**
     * \brief Pesquisa os aeroportos que é possível obter uma ligação direta
     *
     * Complexidade: O(n) em que n é o número de voos encontrados
     */
    void directAirportsAvailable();

    /**
     * \brief Pesquisa os destinos que é possível obter uma ligação direta
     *
     * Complexidade: O(n) em que n é o número de voos encontrados
     */
    void directDestinationsAvailable();

    /**
     * \brief Pesquisa os países que é possível obter uma ligação direta
     *
     * Complexidade: O(n) em que n é o número de voos encontrados
     */
    void directCountriesAvailable();

    /**
     * \brief Pesquisa os aeroportos a que é possível chegar
     *
     * Complexidade: O(|V|)
     */
    void indirectAirportsAvailable(int maxDist);

    /**
     * \brief Pesquisa os destinos a que é possível chegar
     *
     * Complexidade: O(|V|)
     */
    void indirectDestinationsAvailable(int maxDist);

    /**
     * \brief Pesquisa os países a que é possível chegar
     *
     * Complexidade: O(|V|)
     */
    void indirectCountriesAvailable(int maxDist);

    /**
     * Imprime os dados de um determinado aeroporto
     * @param airport Aeroporto
     */
    static void printAirportInfo(Airport airport);
};


#endif //NETWORKMANAGER_MENUINFO_H
