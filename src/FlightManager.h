#ifndef AEDFLIGHTMANAGER_FLIGHTMANAGER_H
#define AEDFLIGHTMANAGER_FLIGHTMANAGER_H

#include <fstream>
#include <iostream>
#include <set>
#include "AirportNetwork.h"

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
    void printNumCountriesFromAirport(std::string airport_name); // 4
    void printNumReachableDests(std::string airport_name, int x); //5
    void printMaxTrip(); // 6
    void printTopKAirport(int k); // 7
    void printEssentialAirports(); // 8

    void testingCalculateDistance();

    // Best flight options
    // ToDo

private:
    AirportNetwork airportNetwork;
    std::set<Airline> airlines;
    // Data parsing
    void processAirlines(std::ifstream &in);
    void processAirports(std::ifstream &in);
    void processFlights(std::ifstream &in);
};

#endif //AEDFLIGHTMANAGER_FLIGHTMANAGER_H
