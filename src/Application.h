#ifndef AEDFLIGHTMANAGER_APPLICATION_H
#define AEDFLIGHTMANAGER_APPLICATION_H

#include <fstream>
#include <sstream>
#include <thread>
#include <iostream>
#include <vector>
#include <cstdlib>

class Application{
public:

    Application(std::string env){
        this->env = env;
    }

    void run(int processedKey);
    void clearScreen();
    static void delay(long sleepTime);
    static int processKey(const std::string& option);

private:
    // Menu options
    std::string showMainMenu();
    void showGoBackMenu(int option, const std::string& functionName);
    void globalNumberOfAvailableFlights();
    void numberOfFlightsOutOfAnAirport();
    void numberOfFlights();
    void numberOfDestinations();
    void flightsWithGreatestNumberOfStops();
    void topAirportsWithGreatestAirCapacity();
    void essentialAirports();
    void checkBestFlightOptions();
    // ToDo

    // System environment variable
    std::string env;
};

#endif //AEDFLIGHTMANAGER_APPLICATION_H
