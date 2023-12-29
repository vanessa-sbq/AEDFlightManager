#include "Application.h"

/**@brief Starts the application.*/
void Application::run(int processedKey) {
    flightManager.parseData();
    //flightManager.debugging(); // ToDo Remove
    L1:
    clearScreen();
    while (processedKey == -1){
        clearScreen();
        processedKey = processKey(showMainMenu());
    }

    switch (processedKey) {
        case 1:
            //globalNumberOfAvailableFlights(); // ToDo
            flightManager.testingCalculateDistance();
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
            // ToDo rere bestbestflightopts();
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
        case 10:
            numberOfCountries();
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
        if (intOPT <= 0 || option.size() > 2) throw std::invalid_argument("NegativeNumber");
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
              << "6 - Show top-k airport with greatest air traffic capacity.\n" // ToDo: user can choose top-k airport
              << "7 - Show essential airports.\n"
              << "8 - Check best flight option(s).\n" // ToDo: Users may want to travel using only some airlines
              << "10 - Show number of countries that an airport/city flies to.\n"  // ToDo: this should be number 4
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
    showGoBackMenu(1, "Show global number of available flights.");
}

void Application::numberOfFlightsOutOfAnAirport() {
    delay(2000);
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
        std::getline(std::cin >> std::ws, city); // Use std::ws to consume whitespaces
        std::cout << "\n";
        std::cout << "Please input country's name: ";
        std::getline(std::cin >> std::ws, country); // Use std::ws to consume whitespaces
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

void Application::numOfDestinationsForGivenAirport(){
    std::cout << "Please input the airport code: ";
    std::string airportCode, opts;
    std::cin >> airportCode;
    L1:
    clearScreen();
    std::cout << "What statistics would you like to see:\n"
    << "1 - Number of airports accessible.\n"
    << "2 - Number of countries accessible.\n"
    << "3 - Number of cities accessible.\n";
    std::cout << "\n*Tip: Multiple options can be selected like this -> 1,3 *\n\n";
    std::cout << "Input: ";

    std::cin >> opts;
    std::stringstream ss(opts);
    std::vector<int> optsSeparated;
    std::string opt;
    std::cout << "\n";

    while (std::getline(ss, opt, ',')) {
        int processedKey = processKey(opt);
        if (processedKey == -1) {
            delay(1000);
            goto L1;
        }
        optsSeparated.push_back(processedKey);
    }

    flightManager.printNumDestinations(airportCode, optsSeparated);

}

void Application::numberOfCountries() {
    L1:
    std::cout << "Choose an option:\n"
              << "1 - Reachable countries from airport\n"
              << "2 - Reachable countries from city\n";

    std::string opt;
    std::cout << "Input: ";
    std::cin >> opt;
    std::cout << "\n";
    clearScreen();

    if(processKey(opt) == 1) {
        std::string airportCode;
        std::cout << "Please input airport code: ";
        std::cin >> airportCode;
        std::cout << "\n";
        delay(1000);
        clearScreen();
        flightManager.printNumCountriesAirport(airportCode);
        delay(2000);
        showGoBackMenu(10, "Show number of countries that an airport/city flies to"); // ToDo: not sure if this works
    }
    if (processKey(opt) == 2){
        std::string city;
        std::cout << "Please input city name: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear buffer
        std::getline(std::cin, city);
        std::cout << "\n";
        delay(1000);
        clearScreen();
        flightManager.printNumCountriesCity(city);
        delay(2000);
        showGoBackMenu(10, "Show number of countries that an airport/city flies to"); // ToDo: not sure if this works
    }
    else {
        goto L1;
    }
}

void Application::numberOfDestinations() {
    std::string airport_code;
    std::cout << "Please input Airport code: ";
    std::cin >> airport_code;
    int x = 0;
    std::cout << "\n";
    std::cout << "Please input Number of Stops: ";
    std::cin >> x;
    std::cout << "\n";
    clearScreen();

L1:
    std::cout << "Choose an option:\n"
              << "1 - Reachable Airports\n"
              << "2 - Reachable Cities\n"
              << "3 - Reachable Countries\n";

    std::string opt;
    std::cout << "Input: ";
    std::cin >> opt;
    std::cout << "\n";
    clearScreen();

    if(processKey(opt) == 1) {
        delay(1000);
        clearScreen();
        flightManager.printNumReachableX(airport_code, x, 0); // ToDo: change function
        delay(2000);
        showGoBackMenu(4, "Show number of destinations (airports, cities, countries) from a given airport in a maximum amount of X stops (lay-overs).");
    }
    if (processKey(opt) == 2){
        delay(1000);
        clearScreen();
        //flightManager.printNumReachableCitiesX(airport_code, x,);   // ToDo: change function
        flightManager.printNumReachableX(airport_code, x, 1); // ToDo: change function
        delay(2000);
        showGoBackMenu(4, "Show number of destinations (airports, cities, countries) from a given airport in a maximum amount of X stops (lay-overs).");
    }
    if (processKey(opt) == 3){
        delay(1000);
        clearScreen();
        //flightManager.printNumReachableCountriesX(airport_code, x);   // ToDo: change function
        flightManager.printNumReachableX(airport_code, x, 2); // ToDo: change function
        delay(2000);
        showGoBackMenu(4, "Show number of destinations (airports, cities, countries) from a given airport in a maximum amount of X stops (lay-overs).");
    } else {
        goto L1;
    }
}

void Application::flightsWithGreatestNumberOfStops() {
    std::string sourceAirport, targetAirport;
    std::cout << "Please input source Airport code: ";
    std::cin >> sourceAirport;
    std::cout << "\n";
    std::cout << "Please input target Airport code: ";
    std::cin >> targetAirport;
    std::cout << "\n";
    flightManager.printMaxTrip();

    delay(2000);
    showGoBackMenu(5, "Show maximum trips (flights with greatest number of stops).");
}

void Application::bestbestflightopts() {
    std::string input1, input2, input3, input4, input5, input6, sourceOpt, targetOpt;
    std::string radius = "ignore";


beginSourceAirport:
    clearScreen();
    std::cout << "How would you like to search for the source Airport ?\n"
    << "1 - Using it's code.\n"
    << "2 - Using it's name.\n"
    << "3 - Using the cities name (all airports considered).\n"
    << "4 - Using coordinates.\n"
    << "Input: ";
    std::cin >> sourceOpt;
    delay(500);

    clearScreen();
    switch (processKey(sourceOpt)) {
        case 1:
            std::cout << "Please input the source Airport's code: ";
            std::cin >> input1;
            input2 = "airportCode";
            break;
        case 2:
            std::cout << "Please input the source Airport's name: ";
            std::getline(std::cin >> std::ws, input1); // Use std::ws to consume whitespaces
            input2 = "airportName";
            break;
        case 3:
            std::cout << "Please input the source City's name: ";
            std::getline(std::cin >> std::ws, input1); // Use std::ws to consume whitespaces
            std::cout << "\n";
            std::cout << "Please input Country's name: ";
            std::getline(std::cin >> std::ws, input5); // Use std::ws to consume whitespaces
            std::cout << "\n";
            input2 = "cityName";
            break;
        case 4:

            if (radius == "ignore"){
                std::cout << "\nnote: You will need to specify a radius (int and in km).\nThis will apply to both source and destination (If destination is provided by coordinates.)\nPlease specify it now: ";
                std::cin >> radius;
            }

            std::cout << "Please input the target latitude: ";
            std::cin >> input1;
            std::cout << "Please input the target longitude: ";
            std::cin >> input2;
            break;
        default:
            goto beginSourceAirport;
    }

beginTargetAirport:
    clearScreen();
    std::cout << "How would you like to search for the target Airport ?\n"
              << "1 - Using it's code.\n"
              << "2 - Using it's name.\n"
              << "3 - Using the cities name (all airports considered).\n"
              << "4 - Using coordinates.\n"
              << "Input: ";
    std::cin >> targetOpt;
    delay(500);

    switch (processKey(targetOpt)) {
        case 1:
            std::cout << "Please input the target Airport's code: ";
            std::cin >> input3;
            input4 = "airportCode";
            break;
        case 2:
            std::cout << "Please input the target Airport's name: ";
            std::getline(std::cin >> std::ws, input3); // Use std::ws to consume whitespaces
            input4 = "airportName";
            break;
        case 3:
            std::cout << "Please input the target City's name: ";
            std::getline(std::cin >> std::ws, input3); // Use std::ws to consume whitespaces
            std::cout << "\n";
            std::cout << "Please input Country's name: ";
            std::getline(std::cin >> std::ws, input6); // Use std::ws to consume whitespaces
            std::cout << "\n";
            input4 = "cityName";
            break;
        case 4:
            if (radius == "ignore"){
                std::cout << "\nnote: You will need to specify a radius (int and in km).\nPlease specify it now: ";
                std::cin >> radius;
            } else {
                L1:
                std::cout << "\nnote: Radius already specified as " << radius << " km.\nWould you like to change it (Y/n)? ";
                string opt;
                cin >> opt;
                for (char& c : opt) c = (char) tolower(c);
                if (opt.size() > 1 || opt != "y" && opt != "n") goto L1;
                if (opt == "y"){
                    std::cout << "\n What value should the radius be: ";
                    std::cin >> radius;
                }
            }

            std::cout << "Please input the target latitude: ";
            std::cin >> input3;
            std::cout << "Please input the target longitude: ";
            std::cin >> input4;
            break;
        default:
            goto beginTargetAirport;
    }

    flightManager.presentTheBestFlightOptions(input1, input2, input3, input4, input5, input6, radius);


    delay(2000);
    showGoBackMenu(5, "turip");
}

void Application::topAirportsWithGreatestAirCapacity() {
    std::cout << "Please input a number for k (number of top airport): ";
    int k = 0;
    std::cin >> k;
    std::cout << "\n";
    clearScreen();
    flightManager.printTopKAirport(k);
    delay(2000);
    showGoBackMenu(6, "Show top-k airport with greatest air traffic capacity.\n");
}

void Application::essentialAirports() {
    delay(2000);
    showGoBackMenu(7, "Show essential airports.");
}

void Application::checkBestFlightOptions() {
    L1:
    std::cout << "Choose an option:\n"
              << "1 - Search without filters.\n"
              << "2 - Filter by airlines.\n"
              << "3 - Filter by least amount of different airlines.\n";

    std::string opt;
    std::cout << "Input: ";
    std::cin >> opt;
    std::cout << "\n";
    clearScreen();

    if(processKey(opt) == 1) {
        // ToDo
    }
    if (processKey(opt) == 2){
        std::string sourceCode;
        std::cout << "Please input the source airport code: ";
        std::getline(std::cin >> std::ws, sourceCode); // Use std::ws to consume whitespaces
        std::cout << "\n";

        std::string destCode;
        std::cout << "Please input the destination airport code: ";
        std::getline(std::cin >> std::ws, destCode); // Use std::ws to consume whitespaces
        std::cout << "\n";

        std::string filteredAirlines;
        std::cout << "Please input preferred airline codes (comma separated): ";
        std::getline(std::cin >> std::ws, filteredAirlines); // Use std::ws to consume whitespaces
        std::cout << "\n";
        clearScreen();
        flightManager.printFlightOptionAirlineFiltered(sourceCode, destCode, filteredAirlines);
        delay(2000);
        showGoBackMenu(8, "Check best flight option(s)."); // ToDo: not sure if this works
    }
    if(processKey(opt) == 3) {
        // ToDo
    }
    else {
        goto L1;
    }
}



