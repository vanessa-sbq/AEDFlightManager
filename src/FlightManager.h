#ifndef AEDFLIGHTMANAGER_FLIGHTMANAGER_H
#define AEDFLIGHTMANAGER_FLIGHTMANAGER_H

#include <fstream>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include <set>
#include "Airline.h"
#include "Graph.h"
#include "Airport.h"

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
    void printNumFlightsCity(const std::string& cityName, const std::string& coutryName); // 3
    void printNumFlightsAirline(const std::string& airlineName); // 3

    void printNumDestinations(const std::string& airportName);

    void printNumCountriesAirport(std::string airportCode); // 4
    void printNumCountriesCity(std::string city); // 4
    void printNumReachableX(const std::string& airport_name, int x, int funcNum); // 5
    void printMaxTrip(); // 6
    void printTopKAirport(int k); // 7
    void printEssentialAirports(); // 8

    void testingCalculateDistance();

    // Best flight options
    // ToDo

private:
    Graph<Airport*> airportNetwork;

    std::unordered_set<Airline* ,HashFunction> airlineSet;
    std::unordered_map<std::string, Airline*> airlineMap;

    std::unordered_map<std::string, Airport*> airportMap;

    // Data parsing
    void processAirlines(std::ifstream &in);
    void processAirports(std::ifstream &in);
    void processFlights(std::ifstream &in);
};

#endif //AEDFLIGHTMANAGER_FLIGHTMANAGER_H
