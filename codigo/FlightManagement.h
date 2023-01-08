#ifndef NETWORKMANAGER_FLIGHTMANAGEMENT_H
#define NETWORKMANAGER_FLIGHTMANAGEMENT_H

#include <unordered_map>
#include <unordered_set>

#include "Airport.h"
#include "Airline.h"
#include "Graph.h"

using namespace std;

/**
 * \brief Classe Flight Management
 *
 * Classe usada para auxiliar o tratamento dos dados
 */
class FlightManagement {
public:
    /**
     * Construtor da classe FlightManagement
     * @param airports path do ficheiro csv com informação relativa aos aeroportos
     * @param airlines path do ficheiro csv com informação relativa às companhias aéreas (airlines)
     * @param flights path do ficheiro com informação relativa aos voos
     */
    FlightManagement(string airports, string airlines, string flights);

    /**
     * \brief Recolhe os dados dos aeroportos a partir de um ficheiro
     *
     * Complexidade: O(n)
     * @param filename Ficheiro com informações dos aeroportos
     * @return
     */
    int getDataAirport(string filename);

    /**
     * \brief Recolhe os dados das companhias aéreas a partir de um ficheiro
     *
     * Complexidade: O(n)
     * @param filename Ficheiro com informações das companhias aéreas
     */
    void getDataAirline(string filename);

    /**
     * \brief Recolhe os dados dos voos a partir de um ficheiro. Responsável por adicionar edges ao grafo.
     *
     * Complexidade: O(n)
     * @param filename Ficheiro com informações dos voos
     */
    void getDataFlights(string filename);

    /**
     * \brief Lê as preferências de companhias aéreas guardadas no ficheiro 'preferences'
     *
     * Complexidade: O(n)
     * @return Preferências de companhias aéreas
     */
    unordered_set<string> readPreferences();

    /**
     * \brief Atualiza o ficheiro preferences com base nas preferências guardadas
     *
     * Complexidade: O(n)
     * @param preferences Preferências de companhias aéreas
     */
    void savePreferences(unordered_set<string> preferences);

    /**
     * \brief Calcula a distância entre dois pontos no globo, dadas as suas coordenadas geográficas
     *
     * Complexidade: O(log(n))
     * @param lat1 Latitude da primeira localizalção
     * @param lon1 Longitude da primeira localizalção
     * @param lat2 Latitude da segunda localização
     * @param lon2 Longitude da segunda localização
     * @return Distância das duas localizações
     */
    static double haversine(double lat1, double lon1, double lat2, double lon2);

    /**
     * Função utilizada para receber input do utilizador na forma de números
     * @param output Mensagem a imprimir no ecrã
     * @return Número recebido como input
     */
    double getNumbers(string output);

    /**
     * Getter do unordered map AirportNode
     * @return unordered map em que a chave é um aeroporto e o valor o número do node correspondente no grafo
     */
    const unordered_map<Airport, int, AirportHash> &getAirportNode() const;
    /**
     * Getter do unordered map NodeAirport
     * @return unordered map em que a chave é o número de node no grafo e o valor o aeroporto correspondente
     */
    const unordered_map<int, const Airport *> &getNodeAirport() const;
    /**
     * Getter do unordered set Airlines
     * @return unordered set contendo as companhias aéreas
     */
    const unordered_set<Airline, AirlineHash> &getAirlines() const;
    /**
     * Getter do unordered map CityAirports
     * @return unordered map em que a chave é uma cidade e o valor uma lista de apontadores de aeroportos
     */
    const unordered_map<string, list<const Airport *>> &getCityAirports() const;
    /**
     * Getter do grafo
     * @return Grafo utilizado para representar os voos
     */
    Graph &getFlights();

private:
    unordered_map<Airport,int, AirportHash> airport_node;
    unordered_map<int, const Airport*> node_airport;
    unordered_set<Airline, AirlineHash> airlines;
    unordered_map<string, list<const Airport*>> city_airports;

    Graph flights;
};


#endif //NETWORKMANAGER_FLIGHTMANAGEMENT_H
