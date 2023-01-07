cmake_minimum_required(VERSION 3.23)
project(networkManager)

set(CMAKE_CXX_STANDARD 14)

add_executable(networkManager codigo/main.cpp codigo/Airport.cpp codigo/Airport.h codigo/Airline.cpp codigo/Airline.h codigo/Graph.cpp codigo/Graph.h codigo/FlightManagement.cpp codigo/FlightManagement.h codigo/Menu.h codigo/Menu.cpp codigo/MenuTravel.cpp codigo/MenuTravel.h codigo/MenuInfo.cpp codigo/MenuInfo.h codigo/MenuPreferences.cpp codigo/MenuPreferences.h codigo/MenuNetworkStats.cpp codigo/MenuNetworkStats.h)
