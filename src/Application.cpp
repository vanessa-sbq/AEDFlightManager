#include "Application.h"

/**@brief Starts the application.*/
void Application::run(int processedKey) {
    flightManager.parseData();
    L1:
    clearScreen();
    while (processedKey == -1){
        clearScreen();
        processedKey = processKey(showMainMenu());
    }

    switch (processedKey) {
        case 1:
            globalNumberOfAvailableFlights(); // ToDo
            std::cout << 1;
            break;
        case 2:
            numberOfFlightsOutOfAnAirport(); // ToDo
            std::cout << 2;
            break;
        case 3:
            numberOfFlights(); // ToDo
            std::cout << 3;
            break;
        case 4:
            numberOfDestinations(); // ToDo
            std::cout << 4;
            break;
        case 5:
            flightsWithGreatestNumberOfStops(); // ToDo
            std::cout << 5;
            break;
        case 6:
            topAirportsWithGreatestAirCapacity(); // ToDo
            std::cout << 6;
            break;
        case 7:
            essentialAirports(); // ToDo
            std::cout << 7;
            break;
        case 8:
            checkBestFlightOptions(); // ToDo
            std::cout << 8;
            break;
        case 9:
            std::cout << "Thank you very much and Bye-Bye.";
            break;
        default:
            goto L1;
    }

    // ToDo
}

void Application::clearScreen() {
    /*if (env == "win")
        L1:
        std::cout << "\n\n\n\n\n\n\n\n\n"
                     "\n\n\n\n\n\n\n\n\n"
                     "\n\n\n\n\n\n\n\n\n"
                     "\n\n\n\n\n\n\n\n\n";
    else if (env == "unix")
        if ( system("clear") == -1 ) goto L1;*/
}

void Application::delay(long sleepMS) {
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepMS));
}

/** @brief Handles the exception thrown by std::stoi. */
int Application::processKey(const std::string& option) {
    try {
        int intOPT = std::stoi(option);
        if (intOPT <= 0 || option.size() != 1) throw std::invalid_argument("NegativeNumber");
        return intOPT;
    } catch (std::invalid_argument& argument) {
        std::cout << "\n* Error while parsing option, please input a valid numeric option. *\n";
        delay(2000);
        return -1;
    }
}

std::string Application::showMainMenu() {
    std::string option;
    std::cout << "\nSelect an operation you would like to do:\n\n"
              << "1 - Show global number of available flights/airports.\n"
              << "2 - Show number of flights out of an airport.\n"  // ToDo: can also filter by airlines
              << "3 - Show number of flights per city/airline.\n"
              << "4 - Show number of destinations (airports, cities, countries)\n"
              << "    from a given airport in a maximum amount of X stops (lay-overs).\n"
              << "5 - Show maximum trips (flights with greatest number of stops).\n"
              << "6 - Show top airports with greatest air capacity.\n" // ToDo: user can choose top-k airport
              << "7 - Show essential airports.\n"
              << "8 - Check best flight option(s).\n" // ToDo: Users may want to travel using only some airlines
              << "9 - Exit.\n";
               // ToDo: 2 or more options are missing


    std::cout << "Input: ";
    std::cin >> option;
    std::cout << "\n";
    return option;
}

void Application::showGoBackMenu(int functionNumber, const std::string& functionName) {
    L1:
    clearScreen();
    std::cout << "\n\nWhat would you like to do next:\n"
    << "1 - Return to main menu.\n"
    << "2 - (again) " << functionName << "\n";

    std::string opt;
    std::cout << "Input: ";
    std::cin >> opt;
    std::cout << "\n";

    int processedKey = processKey(opt);

    switch (processedKey) {
        case -1:
            goto L1;
        case 1:
            // This needs to return to main otherwise when the "new" run method called here returned the program would
            // still keep on executing...
            // This way we are replacing the variable in main and still calling the function run in main
            // the no-no function -> run(-1)
            throw std::invalid_argument("-1");
        case 2:
            // the no-no function -> run(functionNumber)
            throw std::invalid_argument(std::to_string(functionNumber));
        default:
            std::cout << "\n* Error while parsing option, please input a valid numeric option. *\n";
            delay(2000);
            goto L1;
    }
}

void Application::globalNumberOfAvailableFlights() {
    delay(2000);
    flightManager.printGlobalNumAirports();
    flightManager.printGlobalNumFlights();
    showGoBackMenu(1, "Show global number of available flights.");
}

void Application::numberOfFlightsOutOfAnAirport() {
    delay(2000);
    flightManager.printNumFlightsOutOfAirport();
    showGoBackMenu(2, "Show number of flights out of an airport.");
}

void Application::numberOfFlights() {
    L1:
    std::cout << "Choose an option:\n"
    << "1 - Per City\n"
    << "2 - Per AirLine\n";

    std::string opt;
    std::cout << "Input: ";
    std::cin >> opt;
    std::cout << "\n";
    clearScreen();


    if(processKey(opt) == 1) {
        std::string city;
        std::string country;
        std::cout << "Please input city's name: ";
        std::cin >> city;
        std::cout << "\n";
        std::cout << "Please input country's name: ";
        std::cin >> country;
        std::cout << "\n";
        delay(1000);
        clearScreen();

// ToDo -> Ao construir as funções de parsing, fazer com que haja um map com (CityName, CountryName)(Key), AirPort(Value)
        flightManager.printNumFlightsCity(city, country);
        delay(2000);
        showGoBackMenu(3, "Show number of flights per city/airline.");

    }
    if (processKey(opt) == 2){
        std::string airline;
        std::cout << "Please input Airline's code: ";
        std::cin >> airline;
        std::cout << "\n";
        delay(1000);
        clearScreen();
        flightManager.printNumFlightsAirline(airline);
        delay(2000);
        showGoBackMenu(3, "Show number of flights per city/airline.");
    } else {
        goto L1;
    }


}

void Application::numberOfDestinations() {
    delay(2000);
    std::string airport_code = "RYR"; // ToDo: Change this to user input
    int x = 2;                        // ToDo: Change this to user input
    flightManager.printNumReachableDests(airport_code, x);
    showGoBackMenu(4, "Show number of destinations (airports, cities, countries)\nfrom a given airport in a maximum amount of X stops (lay-overs).");
}

void Application::flightsWithGreatestNumberOfStops() {
    delay(2000);
    showGoBackMenu(5, "Show maximum trips (flights with greatest number of stops).");
}

void Application::topAirportsWithGreatestAirCapacity() {
    delay(2000);
    int k = 2;  // ToDo: Change this to user input
    flightManager.printTopKAirport(k);
    showGoBackMenu(6, "Show top airports with greatest air capacity.");
}

void Application::essentialAirports() {
    delay(2000);
    flightManager.printEssentialAirports();
    showGoBackMenu(7, "Show essential airports.");
}

void Application::checkBestFlightOptions() {
    delay(2000);
    showGoBackMenu(8, "Check best flight option(s).");
}



