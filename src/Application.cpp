#include "Application.h"

/**@brief Starts the application.*/
void Application::run(int processedKey) {
    L1:
    clearScreen();
    while (processedKey == -1){
        clearScreen();
        processedKey = processKey(showMainMenu());
    }

    switch (processedKey) {
        case 1:
            globalNumberOfAvailableFlights();
            std::cout << 1;
            break;
        case 2:
            numberOfFlightsOutOfAnAirport();
            std::cout << 2;
            break;
        case 3:
            numberOfFlights();
            std::cout << 3;
            break;
        case 4:
            numberOfCountries();
            break;
        case 5:
            numOfDestinationsForGivenAirport();
            std::cout << 5;
            break;
        case 6:
            numberOfDestinations();
            std::cout << 4;
            break;
        case 7:
            flightsWithGreatestNumberOfStops();
            std::cout << 5;
            break;
        case 8:
            topAirportsWithGreatestAirCapacity();
            std::cout << 6;
            break;
        case 9:
            essentialAirports();
            std::cout << 7;
            break;
        case 10:
            checkBestFlightOptions();
            std::cout << 8;
            break;
        case 11:
            flightManager.dataGoBoom();
            std::cout << "Thank you very much and Bye-Bye.\n";
            break;
        default:
            goto L1;
    }
}

/**
 * @brief clears (or simulates clearing) the screen, depending on the OS used
 */
void Application::clearScreen() {
    if (env == "win")
        L1:
        std::cout << "\n\n\n\n\n\n\n\n\n"
                     "\n\n\n\n\n\n\n\n\n"
                     "\n\n\n\n\n\n\n\n\n"
                     "\n\n\n\n\n\n\n\n\n";
    else if (env == "unix")
        if ( system("clear") == -1 ) goto L1;
}

/**
 * @brief Small delay for design purposes
 */
void Application::delay(long sleepMS) {
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepMS));
}

/** @brief Handles the exception thrown by std::stoi. */
int Application::processKey(const std::string& option) {
    try {
        int intOPT = std::stoi(option);
        if (intOPT <= 0 || option.size() > 2 || intOPT >= 12) throw std::invalid_argument("NegativeNumber");
        return intOPT;
    } catch (std::invalid_argument& argument) {
        std::cout << "\n* Error while parsing option, please input a valid numeric option. *\n";
        delay(2000);
        return -1;
    }
}

/**
 * @brief Shows the main menu
 */
std::string Application::showMainMenu() {
    std::string opti;
    std::cout << "\nSelect an operation you would like to do:\n\n"
              << "1 - Show global number of available flights/airports.\n"

              << "2 - Show number of flights out of an airport.\n"

              << "3 - Show number of flights per city/airline.\n"

              << "4 - Show number of countries that an airport/city flies to.\n"

              << "5 - Show number of destinations for a given airport.\n"

              << "6 - Show number of destinations (airports, cities, countries)\n"
              << "    from a given airport in a maximum amount of X stops (lay-overs).\n"

              << "7 - Show maximum trips (flights with greatest number of stops).\n"

              << "8 - Show top-k airport with greatest air traffic capacity.\n"

              << "9 - Show essential airports.\n"

              << "10 - Check best flight option(s).\n"

              << "11 - Exit.\n";


    std::cout << "Input: ";
    std::cin >> opti;
    std::cout << "\n";
    return opti;
}

/**
 * @brief Shows the go back menu
 */
void Application::showGoBackMenu(int functionNumber, const std::string& functionName) {
    L1:
    std::cout << "\nPress enter to continue";
    std::string a;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, a);
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
            goto L1;
    }
}

/**
 * @brief Calls the corresponding function from the FlightManager
 */
void Application::globalNumberOfAvailableFlights() {
    clearScreen();
    flightManager.printGlobalNums();
    showGoBackMenu(1, "Show global number of available flights.");
}

/**
 * @brief Calls the corresponding function from the FlightManager
 */
void Application::numberOfFlightsOutOfAnAirport() {
    clearScreen();
    flightManager.printNumFlightsOutOfAirport();
    showGoBackMenu(2, "Show number of flights out of an airport.");
}

/**
 * @brief Calls the corresponding function from the FlightManager
 */
void Application::numberOfFlights() {
    L1:
    clearScreen();
    std::cout << "Choose an option:\n"
              << "1 - Per City\n"
              << "2 - Per AirLine\n"
              << "3 - Go back to main menu\n";

    std::string opt;
    std::cout << "Input: ";
    std::cin >> opt;
    std::cout << "\n";
    clearScreen();

    std::string city;
    std::string country;
    std::string airline;
    switch (processKey(opt)) {
        case 1:
            std::cout << "Please input city's name: ";
            std::getline(std::cin >> std::ws, city); // Use std::ws to consume whitespaces
            std::cout << "\n";
            std::cout << "Please input country's name: ";
            std::getline(std::cin >> std::ws, country); // Use std::ws to consume whitespaces
            std::cout << "\n";
            clearScreen();
            flightManager.printNumFlightsCity(city, country);
            break;
        case 2:
            std::cout << "Please input Airline's code: ";
            std::cin >> airline;
            std::cout << "\n";
            clearScreen();
            flightManager.printNumFlightsAirline(airline);
            break;
        case 3:
            throw std::invalid_argument("-1");
        default:
            goto L1;
    }
    showGoBackMenu(3, "Show number of flights per city/airline.");
}

/**
 * @brief Calls the corresponding function from the FlightManager
 */
void Application::numOfDestinationsForGivenAirport(){
    clearScreen();
    std::cout << "Please input the airport code: ";
    std::string airportCode, opts;
    std::cin >> airportCode;
    L1:
    clearScreen();
    std::cout << "What statistics would you like to see:\n"
              << "1 - Number of airports accessible.\n"
              << "2 - Number of countries accessible.\n"
              << "3 - Number of cities accessible.\n"
              << "4 - Go back to main menu\n";
    std::cout << "\n*Tip: Multiple options can be selected like this -> 1,3 *\n\n";
    std::cout << "Input: ";

    std::cin >> opts;
    std::stringstream ss(opts);
    std::vector<int> optsSeparated;
    std::string opt;
    std::cout << "\n";

    while (std::getline(ss, opt, ',')) {
        int processedKey = processKey(opt);
        if (processedKey == 4) throw std::invalid_argument("-1");
        if (processedKey == -1) {
            goto L1;
        }
        optsSeparated.push_back(processedKey);
    }

    flightManager.printNumDestinationsForGivenAirport(airportCode, optsSeparated);
    showGoBackMenu(5, "Show number of destinations for a given airport.");
}

/**
 * @brief Calls the corresponding function from the FlightManager
 */
void Application::numberOfCountries() {
    clearScreen();
    L1:
    std::cout << "Choose an option:\n"
              << "1 - Reachable countries from airport\n"
              << "2 - Reachable countries from city\n"
              << "3 - Go back to main menu\n";

    std::string opt;
    std::cout << "Input: ";
    std::cin >> opt;
    std::cout << "\n";
    clearScreen();

    std::string airportCode;
    std::string city;
    std::string country;
    switch (processKey(opt)){
        case 1:
            std::cout << "Please input airport code: ";
            std::cin >> airportCode;
            std::cout << "\n";
            clearScreen();
            flightManager.printNumCountriesAirport(airportCode);
            break;
        case 2:
            std::cout << "Please input City's name: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear buffer
            std::getline(std::cin, city);
            std::cout << "\n";

            std::cout << "Please input Country's name: ";
            std::cin >> country;
            std::cout << "\n";
            clearScreen();
            flightManager.printNumCountriesCity(city, country);
            break;
        case 3:
            throw std::invalid_argument("-1");
        default:
            goto L1;
    }
    showGoBackMenu(4, "Show number of countries that an airport/city flies to");
}

/**
 * @brief Calls the corresponding function from the FlightManager
 */
void Application::numberOfDestinations() {
    L1:
    clearScreen();
    std::string airport_code;
    std::cout << "Please input Airport code: ";
    std::cin >> airport_code;
    int x = 0;
    std::cout << "\n";
    std::cout << "Please input Number of Stops: ";
    std::cin >> x;
    std::cout << "\n";
    clearScreen();


    std::cout << "Choose an option:\n"
              << "1 - Reachable Airports\n"
              << "2 - Reachable Cities\n"
              << "3 - Reachable Countries\n"
              << "4 - Go back to main menu\n";

    std::string opt;
    std::cout << "Input: ";
    std::cin >> opt;
    std::cout << "\n";
    clearScreen();

    switch(processKey(opt)){
        case 1:
            clearScreen();
            flightManager.printNumReachableX(airport_code, x, 0);
            break;
        case 2:
            clearScreen();
            flightManager.printNumReachableX(airport_code, x, 1);
            break;
        case 3:
            clearScreen();
            flightManager.printNumReachableX(airport_code, x, 2);
            break;
        case 4:
            throw std::invalid_argument("-1");
        default:
            showGoBackMenu(6, "Show number of destinations (airports, cities, countries) from a given airport in a maximum amount of X stops (lay-overs).");
    }
}

/**
 * @brief Calls the corresponding function from the FlightManager
 */
void Application::flightsWithGreatestNumberOfStops() {
    clearScreen();
    flightManager.printMaxTrip();
    showGoBackMenu(7, "Show maximum trips (flights with greatest number of stops).");
}

/**
 * @brief Calls the corresponding function from the FlightManager
 */
void Application::topAirportsWithGreatestAirCapacity() {
    clearScreen();
    std::cout << "Please input a number for k (number of top airport): ";
    int k = 0;
    std::cin >> k;
    std::cout << "\n";
    flightManager.printTopKAirport(k);
    showGoBackMenu(8, "Show top-k airport with greatest air traffic capacity.\n");
}

/**
 * @brief Calls the corresponding function from the FlightManager
 */
void Application::essentialAirports() {
    clearScreen();
    flightManager.printEssentialAirports();
    showGoBackMenu(9, "Show essential airports.");
}

/**
 * @brief Calls the corresponding function from the FlightManager
 */
void Application::checkBestFlightOptions() {
    std::string input1, input2, input3, input4, input5, input6, sourceOpt, targetOpt;
    std::string radius = "ignore";


    clearScreen();
    beginSourceAirport:
    std::cout << "\nHow would you like to search for the source Airport ?\n"
              << "1 - Using it's code.\n"
              << "2 - Using it's name.\n"
              << "3 - Using the cities name (all airports considered).\n"
              << "4 - Using coordinates.\n"
              << "5 - Go back to main menu\n"
              << "Input: ";
    std::cin >> sourceOpt;


    switch (processKey(sourceOpt)) {
        case 1:
            std::cout << "\n";
            std::cout << "Please input the source Airport's code: ";
            std::cin >> input1;
            input2 = "airportCode";
            break;
        case 2:
            std::cout << "\n";
            std::cout << "Please input the source Airport's name: ";
            std::getline(std::cin >> std::ws, input1); // Use std::ws to consume whitespaces
            input2 = "airportName";
            break;
        case 3:
            std::cout << "\n";
            std::cout << "Please input the source City's name: ";
            std::getline(std::cin >> std::ws, input1);
            std::cout << "\n";
            std::cout << "Please input Country's name: ";
            std::getline(std::cin >> std::ws, input5);
            std::cout << "\n";
            input2 = "cityName";
            break;
        case 4:

            if (radius == "ignore"){
                std::cout << "\nnote: You will need to specify a radius (int and in km).\nThis will apply to both source and destination (If destination is provided by coordinates.)\nPlease specify it now: ";
                std::cin >> radius;
            }

            std::cout << "\n";
            std::cout << "Please input the target latitude: ";
            std::cin >> input1;
            std::cout << "\n";
            std::cout << "Please input the target longitude: ";
            std::cin >> input2;
            std::cout << "\n";
            break;
        case 5:
            throw std::invalid_argument("-1");
        default:
            goto beginSourceAirport;
    }

    beginTargetAirport:
    clearScreen();
    std::cout << "\nHow would you like to search for the target Airport ?\n"
              << "1 - Using it's code.\n"
              << "2 - Using it's name.\n"
              << "3 - Using the cities name (all airports considered).\n"
              << "4 - Using coordinates.\n"
              << "5 - Go back to main menu\n"
              << "Input: ";
    std::cin >> targetOpt;

    switch (processKey(targetOpt)) {
        case 1:
            std::cout << "\n";
            std::cout << "Please input the target Airport's code: ";
            std::cin >> input3;
            input4 = "airportCode";
            break;
        case 2:
            std::cout << "\n";
            std::cout << "Please input the target Airport's name: ";
            std::getline(std::cin >> std::ws, input3);
            input4 = "airportName";
            break;
        case 3:
            std::cout << "\n";
            std::cout << "Please input the target City's name: ";
            std::getline(std::cin >> std::ws, input3);
            std::cout << "\n";
            std::cout << "Please input Country's name: ";
            std::getline(std::cin >> std::ws, input6);
            std::cout << "\n";
            input4 = "cityName";
            break;
        case 4:
            if (radius == "ignore"){
                std::cout << "\nnote: You will need to specify a radius (int and in km).\nPlease specify it now: ";
                std::cin >> radius;
                std::cout << "\n";
            } else {
                radRed:
                std::cout << "\nnote: Radius already specified as " << radius << " km.\nWould you like to change it (Y/n)? ";
                string opt;
                cin >> opt;
                std::cout << "\n";
                for (char& c : opt) c = (char) tolower(c);
                if (opt.size() > 1 || opt != "y" && opt != "n") goto radRed;
                if (opt == "y"){
                    std::cout << "\n What value should the radius be: ";
                    std::cin >> radius;
                }
            }

            std::cout << "\n";
            std::cout << "Please input the target latitude: ";
            std::cin >> input3;
            std::cout << "Please input the target longitude: ";
            std::cin >> input4;
            break;
        case 5:
            throw std::invalid_argument("-1");
        default:
            goto beginTargetAirport;
    }
    clearScreen();

    pair<vector<Vertex<Airport*>*>, vector<Vertex<Airport*>*>> converted = flightManager.getConvertedVertexesFromUser(input1, input2, input3, input4, input5, input6, radius);

    if (converted.first.empty() || converted.second.empty()){
        std::cout << "";
        goto beginSourceAirport;
    }

    L1:
    std::cout << "Choose an option:\n"
              << "1 - Search without filters.\n"
              << "2 - Filter by airlines.\n"
              << "3 - Filter by least amount of different airlines.\n"
              << "4 - Go back to main menu\n";

    std::string opt;
    std::cout << "Input: ";
    std::cin >> opt;
    std::cout << "\n";
    clearScreen();

    std::string sourceCode;
    std::string destCode;
    std::string filteredAirlines;
    switch (processKey(opt)) {
        case 1:
            flightManager.printFlightOptionAirlineFiltered(converted.first, converted.second, filteredAirlines, true);
            break;
        case 2:
            std::cout << "Please input preferred airline codes (comma separated): ";
            std::getline(std::cin >> std::ws, filteredAirlines);
            std::cout << "\n";
            clearScreen();
            flightManager.printFlightOptionAirlineFiltered(converted.first, converted.second, filteredAirlines, false);
            break;
        case 3:
            clearScreen();
            flightManager.printFlightOptionMinimalAirlines(converted.first, converted.second);
            break;
        case 4:
            throw std::invalid_argument("-1");
        default:
            goto L1;
    }
    showGoBackMenu(10, "Check best flight option(s).");
}
