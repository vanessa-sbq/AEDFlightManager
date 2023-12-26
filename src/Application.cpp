#include "Application.h"
#include <string>
#include <thread>

/**@brief Starts the application.*/
void Application::run() {
    clearScreen();
    showMainMenu();
    // ToDo
}

void Application::clearScreen() {
    // ToDo
}

void Application::showMainMenu() {
    while (true) {
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

        // Probably outdated
        std::cout << "Input: ";
        std::cin >> option;
        std::cout << std::endl;
        clearScreen();
        switch(option){
            case 1:
                std::cout << "AAAA";
                break;
            default:
                std::cout << "Invalid option...";
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                clearScreen();
                continue;
        }
        //

    }

}



