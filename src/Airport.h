//
// Created by vascocosta on 12/26/23.
//

#ifndef AEDFLIGHTMANAGER_AIRPORT_H
#define AEDFLIGHTMANAGER_AIRPORT_H


#include <string>
#include <vector>
#include "Flight.h"

class Flight;
class Airport {
    // airport info:
    std::pair<double, double> positionInfo;
    std::string code;
    std::string name;
    std::string city;
    std::string country;
    // graph stuff:
    std::vector<Flight> destinations;
    bool visited;
    int indegree;

public:
    Airport(const std::pair<double,double> p,
            std::string code,
            std::string name,
            std::string city,
            std::string country);

    const std::pair<double, double> &getPositionInfo() const;
    const std::string &getCode() const;
    const std::string &getName() const;
    const std::string &getCity() const;
    const std::string &getCountry() const;

    const std::vector<Flight> &getDestinations() const;
    bool isVisited() const;
    void setVisited(bool value);
    std::pair<double, double> getInfo();
    int getIndegree() const;
    int setIndegree(int indegree);

    bool addDestination(Flight &flight);
    bool operator == (const Airport &p2) const;

    //friend class AirportNetwork;  // ToDo: remove?
};


#endif //AEDFLIGHTMANAGER_AIRPORT_H
