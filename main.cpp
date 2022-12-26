#include "FlightManagement.h"

int main() {
    FlightManagement management = FlightManagement();
    management.getDataAirport("../dataset/airports.csv");
    management.getDataAirline("../dataset/airlines.csv");
    return 0;
}
