cmake_minimum_required(VERSION 3.23)
project(networkManager)

set(CMAKE_CXX_STANDARD 14)

add_executable(networkManager main.cpp Airport.cpp Airport.h Airline.cpp Airline.h Graph.cpp Graph.h FlightManagement.cpp FlightManagement.h Menu.h Menu.cpp MenuTravel.cpp MenuTravel.h MenuInfo.cpp MenuInfo.h MenuPreferences.cpp MenuPreferences.h MenuNetworkStats.cpp MenuNetworkStats.h)
