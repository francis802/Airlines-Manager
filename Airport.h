#ifndef NETWORKMANAGER_AIRPORT_H
#define NETWORKMANAGER_AIRPORT_H

#include <string>

using namespace std;

class Airport {
public:
    Airport(const string &code, const string &name, const string &city, double latitude, double longitude);

    const string &getCode() const;
    const string &getName() const;
    const string &getCity() const;
    double getLatitude() const;
    double getLongitude() const;

    bool operator==(const Airport &rhs) const;

private:
    string code;
    string name;
    string city;
    double latitude;
    double longitude;
};

struct AirportHash{
    int operator() (const Airport& airport) const{
        return (((((hash<string>() (airport.getCode())
                    ^ (hash<string>() (airport.getName()) << 1)) >> 1)
                  ^ (hash<string>() (airport.getCity()) << 1) >> 1)
                 ^ (hash<double>() (airport.getLatitude()) << 1) >> 1)
                ^ (hash<double>() (airport.getLongitude()) << 1) >> 1);
    }

    bool operator() (const Airport& a1, const Airport& a2) const{
        return a1.getCode() == a2.getCode();
    }
};

#endif //NETWORKMANAGER_AIRPORT_H
