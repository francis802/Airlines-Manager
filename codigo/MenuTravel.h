#ifndef NETWORKMANAGER_MENUTRAVEL_H
#define NETWORKMANAGER_MENUTRAVEL_H


#include <list>
#include <queue>
#include "Menu.h"

/**
 * \brief Classe MenuTravel
 *
 * Classe filha da classe Menu utilizada para obter o menor número de voos necessário para ir de um ponto a outro
 */
class MenuTravel: public Menu {
public:
    /**
     * Construtor da classe MenuTravel
     * @param management
     */
    explicit MenuTravel(const FlightManagement& management);

    /**
     * Inicializa o MenuTravel, é responsável pelas chamadas às funções para obter e imprimir o menor caminho
     * @return false para continuar o programa, true para sair
     */
    bool start();

    /**
     * Função recursiva que percorre e imprime todos os caminhos determinados pela pesquisa em largura
     * @param current_path Path atual
     */
    void getPath(list<int> current_path);

    /**
     * \brief Procura aeroportos com base no input do utilizador
     *
     * Complexidade: O(n*log(n)) - pior caso em que é escolhida a opção de pesquisa por localização geográfica
     * @return Fila contendo todos os aeroportos correspondentes à pesquisa
     */
    queue<int> getAirports();

    /**
     * Imprime as companhias aéreas que podem ser utilizadas para um determinado voo
     * @param dep Iterador do aeroporto de partida
     * @param arr Iterador do aeroporto de chegada
     * @param preferences Preferências de companhias aéreas a serem utilizadas
     */
    void getAirlines(list<int>::iterator dep, list<int>::iterator arr, unordered_set<string> preferences);
};


#endif //NETWORKMANAGER_MENUTRAVEL_H
