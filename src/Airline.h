#ifndef AEDFLIGHTMANAGER_AIRLINE_H
#define AEDFLIGHTMANAGER_AIRLINE_H

#include <string>

/**@brief Represents an airline.*/
class Airline {
    std::string code;
    std::string name;
    std::string callsign;
    std::string country;

public:
    Airline(std::string code, std::string name, std::string country, std::string callsign = "_");
    const std::string &getCode() const;
    bool operator<(const Airline &other) const;
    bool operator==(const Airline &other) const;
};


#endif //AEDFLIGHTMANAGER_AIRLINE_H
