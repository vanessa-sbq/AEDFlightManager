#ifndef AEDFLIGHTMANAGER_AIRPORT_H
#define AEDFLIGHTMANAGER_AIRPORT_H

#include <string>
#include <vector>

/**@brief Represents an airport.*/
class Airport {
    // airport info:
    std::pair<double, double> positionInfo;
    std::string code;
    std::string name;
    std::string city;
    std::string country;

public:
    Airport(std::pair<double,double> p,
            std::string code,
            std::string name,
            std::string city,
            std::string country);

    const std::pair<double, double> &getPositionInfo() const;
    const std::string &getCode() const;
    const std::string &getCity() const;
    const std::string &getCountry() const;

    bool operator == (const Airport &p2) const;
    bool operator < (const Airport &p2) const;
};

#endif //AEDFLIGHTMANAGER_AIRPORT_H
