#ifndef NETWORKMANAGER_AIRLINE_H
#define NETWORKMANAGER_AIRLINE_H

#include <string>

using namespace std;

class Airline {
public:
    Airline(const string &code, const string &name, const string &callsign, const string &country);

    const string &getCode() const;
    const string &getName() const;
    const string &getCallsign() const;
    const string &getCountry() const;

    bool operator==(const Airline &rhs) const;

private:
    string code;
    string name;
    string callsign;
    string country;
};

struct AirlineHash{
    int operator() (const Airline& airline) const{
        return ((((hash<string>() (airline.getCode())
                    ^ (hash<string>() (airline.getName()) << 1)) >> 1)
                  ^ (hash<string>() (airline.getCallsign()) << 1) >> 1)
                 ^ (hash<string>() (airline.getCountry()) << 1) >> 1);
    }

    bool operator() (const Airline& a1, const Airline& a2) const{
        return a1.getCode() == a2.getCode();
    }
};

#endif //NETWORKMANAGER_AIRLINE_H
