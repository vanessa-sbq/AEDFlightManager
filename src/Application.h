#ifndef AEDFLIGHTMANAGER_APPLICATION_H
#define AEDFLIGHTMANAGER_APPLICATION_H

#include <iostream>

class Application{
public:
    void run();
    void clearScreen();

private:
    // Menu options
    void showMainMenu();
    // ToDo

    // System environment variable
    std::string env;
};

#endif //AEDFLIGHTMANAGER_APPLICATION_H
