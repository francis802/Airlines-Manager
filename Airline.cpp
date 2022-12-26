#include "Airline.h"

Airline::Airline(const string &code, const string &name, const string &callsign, const string &country) : code(code),
    name(name), callsign(callsign), country(country) {}

const string &Airline::getCode() const {
    return code;
}

const string &Airline::getName() const {
    return name;
}

const string &Airline::getCallsign() const {
    return callsign;
}

const string &Airline::getCountry() const {
    return country;
}

bool Airline::operator==(const Airline &rhs) const {
    return code == rhs.code;
}
