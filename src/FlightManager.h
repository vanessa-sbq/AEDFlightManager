#ifndef AEDFLIGHTMANAGER_FLIGHTMANAGER_H
#define AEDFLIGHTMANAGER_FLIGHTMANAGER_H

#include <fstream>
#include <iostream>

/**@brief Class that does operations on the data.*/
class FlightManager{
public:
    // Constructor
    FlightManager();

    // Data parsing
    void parseData();

    // Network statistics
    void printGlobalNumAirports(); // 1
    void printGlobalNumFlights(); // 1
    void printNumFlightsOutOfAirport(); // 2
    void printNumFlightsCityAirline(); // 3
    void printNumCountriesFromAirport(); // 4
    void printNumReachableDests(); //5
    void printMaxTrip(); // 6
    void printTopKAirport(); // 7
    void printEssentialAirports(); // 8

    // Best flight options
    // ToDo

private:
    // Data parsing
    void processAirlines(std::ifstream &in);
    void processAirports(std::ifstream &in);
    void processFlights(std::ifstream &in);
};

#endif //AEDFLIGHTMANAGER_FLIGHTMANAGER_H
