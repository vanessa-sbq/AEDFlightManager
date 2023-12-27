#include "FlightManager.h"

FlightManager::FlightManager(){}

void FlightManager::parseData(){
    std::ifstream in;

    // Open the file using the provided path.
    in.open("../inputFiles/airlines.csv");
    if (!in.is_open()){
        std::cout << "Unable to open airlines.csv.\n";
        return;
    }
    processAirlines(in);
    in.close();

    in.open("../inputFiles/airports.csv");
    if (!in.is_open()){
        std::cout << "Unable to open airports.csv.\n";
        return;
    }
    processAirports(in);
    in.close();

    in.open("../inputFiles/flights.csv");
    if (!in.is_open()){
        std::cout << "Unable to open flights.csv.\n";
        return;
    }
    processFlights(in);
    in.close();
}

void FlightManager::processAirlines(std::ifstream &in){

}
void FlightManager::processAirports(std::ifstream &in){

}
void FlightManager::processFlights(std::ifstream &in){

}


// 1
void FlightManager::printGlobalNumAirports(){
    // ToDo
}
void FlightManager::printGlobalNumFlights(){
    // ToDo
}


// 2
void FlightManager::printNumFlightsOutOfAirport(){
    // ToDo
}


// 3
void FlightManager::printNumFlightsCityAirline(){
    // ToDo
}


// 4
void FlightManager::printNumCountriesFromAirport(std::string airport_name){
    // ToDo
    std::cout << airport_name;
    // algorithm:
    // 1. traverse adjacency list of airport
    // 2. print all country names of the list
}


// 5
void FlightManager::printNumReachableDests(std::string airport_code, int x){
    // ToDo
    std::cout << airport_code;
    // algorithm:
    // 1. bfs for all distances until x
    // 2. count number of airports, cities, countries (separately)
    // 3. print counts
}


// 6
void FlightManager::printMaxTrip(){
    // ToDo
}


// 7
void FlightManager::printTopKAirport(int k){
    // ToDo
    for (Airport* airport : airportNetwork.getAirports()){
        // DEBUG
        std::cout << airport->getDestinations().size();
        std::cout << "AAA";
    }
    // algorithm:
    // 1. k is the number of times a max is skipped
    // 2. Find the next max until k is 0
    // 3. print the k-th airport
}


// 8
void FlightManager::printEssentialAirports(){
    // ToDo
}

void FlightManager::testingCalculateDistance() {
    double lat1,lat2,long1,long2;
    std::cout << "lat 1 = "; std::cin >> lat1;
    std::cout << "lat 2 = "; std::cin >> lat2;
    std::cout << "long 1 = "; std::cin >> long1;
    std::cout << "long 2 = "; std::cin >> long2;

    double res = airportNetwork.calculateDistance(std::pair<double, double>(lat1, long1), std::pair<double, double>(lat2, long2));
    std::cout << "distance = " << res;
}
