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
    /** @brief Print the number of flights that a city has.
     *  @details The number of flights is considered to be out-degree (Flights that have this Airport as source)
     *  @details plus it's in-degree (Flights that have this Airport as destination).
     *  @details The Time Complexity should be O(1 + cityNameSize + coutryNameSize) however, if a city has more than one Airport then
     *  @details Time Complexity will be O(Number of Airports of that City + cityNameSize + coutryNameSize).
     *  @details Also, due to the use of an hashmap, in the worst case the Time Complexity can be O(n + cityNameSize + coutryNameSize)
     *  @details or even O(n + Number of Airports of that City + cityNameSize + coutryNameSize) where n is the size of the hashmap.
    * */
void FlightManager::printNumFlightsCity(const std::string& cityName, const std::string& coutryName){
// Preciso de uma forma de ter um nome de uma cidade e saber os aeroportos que esta tem.
// Uma cidade pode ter mais que um aeroporto.

    // All names should be lowercase to make searching easier.
    std::string cityNameDup = cityName;
    for (char &c: cityNameDup) c = (char) std::tolower(static_cast<unsigned char>(c));

    std::string coutryNameDup = coutryName;
    for (char &c: coutryNameDup) c = (char) std::tolower(static_cast<unsigned char>(c));

    // Get the unordered map and find the city.
        std::unordered_map<std::pair<std::string,std::string>, std::vector<Airport*>, PairHash> airports = airportNetwork.getCountryAirports();
    auto foundCityAirports = airports.find({cityNameDup, coutryNameDup});

    // Case where there is no city with the given name was found.
    if (foundCityAirports == airports.end()){
        std::cout << "No city named " << cityName << " of country " << coutryName << " exists.\n";
        return;
    }

    // Get total number of flights.
    unsigned long totalFlights = 0;
    for (Airport* airport : foundCityAirports->second){
        totalFlights += airport->getDestinations().size();
        totalFlights += airport->getIndegree();
    }

    std::cout << "The number of flights for " << cityName << ", " << coutryName << " is " << totalFlights << ".\n";
}

void FlightManager::printNumFlightsAirline(const std::string& airlineName){

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
