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

// Custom hash function for std::pair
namespace std {
    template <typename T1, typename T2>
    struct hash<std::pair<T1, T2>> {
        size_t operator()(const std::pair<T1, T2>& p) const {
            auto h1 = std::hash<T1>{}(p.first);
            auto h2 = std::hash<T2>{}(p.second);

            // A simple way to combine the hash values
            return h1 ^ h2;
        }
    };
}

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

    void printNumDestinations(const std::string& airportCode, std::vector<int> filters);

    void printNumCountriesAirport(const std::string& airportCode); // 4
    void printNumCountriesCity(const std::string& city, const std::string & country); // 4
    void printNumReachableX(const std::string& airport_name, int x, int funcNum); // 5
    void printMaxTrip(); // 6
    void printTopKAirport(int k); // 7
    void printEssentialAirports(); // 8
    void printFlightOptionMinimalAirlines(); // 9


    void printFlightOptionAirlineFiltered(vector<Vertex<Airport*>*> source , vector<Vertex<Airport*>*> dest, const string& filteredAirlines, bool ignoreFilter); // 9


    pair<vector<Vertex<Airport*>*>, vector<Vertex<Airport*>*>> getConvertedVertexesFromUser(const string& input1,const string& input2, const string& input3, const string& input4, const string& input5, const string& input6, const string& radius);

    void testingCalculateDistance();

    // Best flight options
    // ToDo

private:
    Graph<Airport*> airportNetwork;

    std::unordered_set<Airline* ,HashFunction> airlineSet;
    std::unordered_map<std::string, Airline*> airlineMap;

    // Airports by code
    std::unordered_map<std::string, Airport*> airportMap;

    // Airports by name
    std::unordered_map<std::string, Airport*> airportNameMap;

    // Airports by cities, countries
    std::unordered_map<pair<std::string, std::string>, vector<Airport*>> airportCityMap;

    // Auxiliary functions
    int numberOfFlights(Vertex<Airport*>* airport);  // auxiliary function

    // Data parsing
    void processAirlines(std::ifstream &in);
    void processAirports(std::ifstream &in);
    void processFlights(std::ifstream &in);
};

#endif //AEDFLIGHTMANAGER_FLIGHTMANAGER_H
