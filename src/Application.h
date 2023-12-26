#ifndef AEDFLIGHTMANAGER_APPLICATION_H
#define AEDFLIGHTMANAGER_APPLICATION_H

#include <iostream>

/**@brief Class that manages the menu.*/
class Application{
public:
    void run();
    void clearScreen();

private:
    // Menu options
    void showMainMenu();
    // ToDo

    // Attributes
    std::string env; // System environment variable
    int option;
};


#endif //AEDFLIGHTMANAGER_APPLICATION_H
