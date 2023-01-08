#ifndef NETWORKMANAGER_AIRPORT_H
#define NETWORKMANAGER_AIRPORT_H

#include <string>

using namespace std;

/**
 * \brief Classe Airport
 *
 * Um aeroporto é definido pelo seu código IATA, nome, cidade, país, longitude e latitude
 */
class Airport {
public:
    /**
     * Construtor default da classe Airport
     */
    Airport();

    /**
     * Construtor da classe Airport
     * @param code Código IATA
     */
    Airport(const string &code);

    /**
     * Construtor da classe Airport
     * @param code Código IATA
     * @param name Nome
     * @param city Cidade
     * @param country País
     * @param latitude Latitude
     * @param longitude Longitude
     */
    Airport(const string &code, const string &name, const string &city, const string &country, double latitude, double longitude);

    /**
     * Getter do código do aeroporto
     * @return Código IATA do aeroporto
     */
    const string &getCode() const;

    /**
     * Getter do nome do aeroporto
     * @return Nome do aeroporto
     */
    const string &getName() const;

    /**
     * Getter da cidade do aeroporto
     * @return Cidade em que se situa o aeroporto
     */
    const string &getCity() const;

    /**
     * Getter do país em que se encontra o aeroporto
     * @return País em que se situa o aeroporto
     */
    const string &getCountry() const;

    /**
     * Getter da latitude do aeroporto
     * @return Latitude em que se situa o aeroporto
     */
    double getLatitude() const;

    /**
     * Getter da longitude do aeroporto
     * @return Longitude em que se situa o aeroporto
     */
    double getLongitude() const;

    /**
     * Overload do operator "=="
     * @param rhs Airport a comparar
     * @return true se o código IATA dos aeroportos for igual, false caso contrário
     */
    bool operator==(const Airport &rhs) const;

private:
    string code;
    string name;
    string city;
    string country;
    double latitude;
    double longitude;
};

/**
 * Hash Function para objetos da classe Airport
 */
struct AirportHash{
    size_t operator() (Airport const& airport) const{
        return hash<string>() (airport.getCode());
    }
};

#endif //NETWORKMANAGER_AIRPORT_H
