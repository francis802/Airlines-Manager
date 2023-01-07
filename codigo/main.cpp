#include "FlightManagement.h"
#include "Menu.h"

int main() {
    FlightManagement management = FlightManagement("../dataset/airports.csv",
                                                   "../dataset/airlines.csv",
                                                   "../dataset/flights.csv");
    Menu menu = Menu(management);
    menu.start();
    return 0;
}
