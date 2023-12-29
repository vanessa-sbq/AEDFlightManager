#ifndef AEDFLIGHTMANAGER_FLIGHTMANAGER_H
#define AEDFLIGHTMANAGER_FLIGHTMANAGER_H

#include <fstream>
#include <iostream>
#include <unordered_set>
#include <set>
#include <sstream>
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

    void printNumCountriesFromAirport(std::string airport_name); // 4
    void printNumReachableDests(std::string airport_name, int x); //5
    void printMaxTrip(); // 6
    void printTopKAirport(int k); // 7
    void printEssentialAirports(); // 8

    void presentTheBestFlightOptions(const string& input1,const string& input2, const string& input3, const string& input4, const string& input5, const string& input6, const string& radius);


    /*void debugging(){
        for (auto iter : airportCityMap){
            std::cout << "The city with name " << iter.first << " has a total of " << iter.second.size() << " airports which are: ";
            for (auto a : iter.second){
                cout << " " << a->getCode() << " ";
            }
            cout << "\n";
        }
    }*/

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

    // Data parsing
    void processAirlines(std::ifstream &in);
    void processAirports(std::ifstream &in);
    void processFlights(std::ifstream &in);
};

#endif //AEDFLIGHTMANAGER_FLIGHTMANAGER_H
