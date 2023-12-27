#include "FlightManager.h"


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
void FlightManager::printNumCountriesFromAirport(){
    // ToDo
}


// 5
void FlightManager::printNumReachableDests(){
    // ToDo
}


// 6
void FlightManager::printMaxTrip(){
    // ToDo
}


// 7
void FlightManager::printTopKAirport(){
    // ToDo
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

FlightManager::FlightManager() = default;
