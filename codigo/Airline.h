#ifndef NETWORKMANAGER_AIRLINE_H
#define NETWORKMANAGER_AIRLINE_H

#include <string>

using namespace std;

/**
 * \brief Classe Airline
 *
 * Uma airline (companhia aérea) é definida pelo seu código ICAO,nome oficial, alcunha e país de origem.
 */
class Airline {
public:
    /**
     * Construtor da classe Airline
     * @param code Código ICAO da companhia
     */
    Airline(const string &code);

    /**
     * Construtor da classe Airline
     * @param code Código ICAO
     * @param name Nome oficial
     * @param callsign Alcunha
     * @param country País de origem
     */
    Airline(const string &code, const string &name, const string &callsign, const string &country);

    /**
     * Getter do código da companhia
     * @return Código ICAO da compahia
     */
    const string &getCode() const;

    /**
     * Getter do país de origem da companhia
     * @return País de origem da companhia
     */
    const string &getCountry() const;

    /**
     * Overload do operator "=="
     * @param rhs Airline para comparar
     * @return true se o código das duas companhias aéreas for igual, false caso contrário
     */
    bool operator==(const Airline &rhs) const;

private:
    string code;
    string name;
    string callsign;
    string country;
};

/**
 * Hash Function para objetos da classe Airline
 */
struct AirlineHash{
    size_t operator() (Airline const& airline) const{
        return hash<string>() (airline.getCode());
    }
};

#endif //NETWORKMANAGER_AIRLINE_H
