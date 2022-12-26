#include "Airport.h"

Airport::Airport(const string &code, const string &name, const string &city, double latitude, double longitude) : code(
        code), name(name), city(city), latitude(latitude), longitude(longitude) {}

const string &Airport::getCode() const {
    return code;
}

const string &Airport::getName() const {
    return name;
}

const string &Airport::getCity() const {
    return city;
}

double Airport::getLatitude() const {
    return latitude;
}

double Airport::getLongitude() const {
    return longitude;
}

bool Airport::operator==(const Airport &rhs) const {
    return code == rhs.code;
}
