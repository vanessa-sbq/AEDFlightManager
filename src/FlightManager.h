#ifndef AEDFLIGHTMANAGER_FLIGHTMANAGER_H
#define AEDFLIGHTMANAGER_FLIGHTMANAGER_H

/**@brief Class that does operations on the data.*/
class FlightManager{
public:
    // Network statistics
    void parseData();
    // 1
    void printGlobalNumAirports();
    void printGlobalNumFlights();
    // 2
    void printNumFlightsOutOfAirport();
    // 3
    void printNumFlightsCityAirline();
    // 4
    void printNumCountriesFromAirport();
    // 5
    void printNumReachableDests();
    // 6
    void printMaxTrip();
    // 7
    void printTopKAirport();
    // 8
    void printEssentialAirports();

    // Best flight options
    // ToDo

private:
    // ToDo
};

#endif //AEDFLIGHTMANAGER_FLIGHTMANAGER_H
