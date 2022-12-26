#ifndef NETWORKMANAGER_AIRPORT_H
#define NETWORKMANAGER_AIRPORT_H

#include <string>

using namespace std;

class Airport {
public:
    Airport(const string &code);
    Airport(const string &code, const string &name, const string &city, const string &country, double latitude, double longitude);

    const string &getCode() const;
    const string &getName() const;
    const string &getCity() const;
    const string &getCountry() const;
    double getLatitude() const;
    double getLongitude() const;

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
        return ((((((hash<string>() (airport.getCode())
                    ^ (hash<string>() (airport.getName()) << 1)) >> 1)
                  ^ (hash<string>() (airport.getCity()) << 1) >> 1)
                 ^ (hash<string>() (airport.getCountry()) << 1) >> 1)
                 ^ (hash<double>() (airport.getLatitude()) << 1) >> 1)
                ^ (hash<double>() (airport.getLongitude()) << 1) >> 1);
    }
};

#endif //NETWORKMANAGER_AIRPORT_H
