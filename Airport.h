#ifndef NETWORKMANAGER_AIRPORT_H
#define NETWORKMANAGER_AIRPORT_H

#include <string>

using namespace std;

class Airport {
public:
    Airport();
    Airport(const string &code);
    Airport(const string &code, const string &name, const string &city, const string &country, double latitude, double longitude);

    const string &getCode() const;
    const string &getName() const;
    const string &getCity() const;
    const string &getCountry() const;
    double getLatitude() const;
    double getLongitude() const;

    void setName(const string &name);

    bool operator==(const Airport &rhs) const;

private:
    string code;
    string name;
    string city;
    string country;
    double latitude;
    double longitude;
};

struct AirportHash{
    size_t operator() (Airport const& airport) const{
        return hash<string>() (airport.getCode());
    }
};

#endif //NETWORKMANAGER_AIRPORT_H
