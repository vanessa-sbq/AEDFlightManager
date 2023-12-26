#include "Application.h"

/*
 * Starts the application.
 */
void Application::run() {
    L1:
    clearScreen();
    int processedKey = processKey(showMainMenu());
    while (processedKey == -1){
        clearScreen();
        processedKey = processKey(showMainMenu());
    }

    switch (processedKey) {
        case 1:
            // ToDo
            std::cout << 1;
            break;
        case 2:
            // ToDo
            std::cout << 2;
            break;
        case 3:
            // ToDo
            std::cout << 3;
            break;
        case 4:
            // ToDo
            std::cout << 4;
            break;
        case 5:
            // ToDo
            std::cout << 5;
            break;
        case 6:
            // ToDo
            std::cout << 6;
            break;
        case 7:
            // ToDo
            std::cout << 7;
            break;
        case 8:
            // ToDo
            std::cout << "Thank-You very much and Bye-Bye.";
            break;
        default:
            goto L1;
    }

    // ToDo
}

void Application::clearScreen() {
    // ToDo
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
              << "1 - Show global number of available flights.\n"
              << "2 - Show number of flights out of an airport.\n"  // ToDo: can also filter by airlines
              << "3 - Show number of flights per city/airline.\n"
              << "4 - Show number of destinations (airports, cities, countries)\n"
              << "    from a given airport in a maximum amount of X stops (lay-overs).\n"
              << "5 - Show maximum trips (flights with greatest number of stops).\n"
              << "6 - Show top airports with greatest air capacity.\n" // ToDo: user can choose top-k airport
              << "7 - Show essential airports.\n"
              << "8 - Exit.\n";


    std::cout << "Input: ";
    std::cin >> option;
    std::cout << "\n";
    return option;
}



