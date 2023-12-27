//
// Created by vascocosta on 12/26/23.
//

#include "Airport.h"

Airport::Airport(const std::pair<double, double> p,
                 std::string code,
                 std::string name,
                 std::string city,
                 std::string country) :
        positionInfo(p),
        code(code),
        name(name),
        city(city),
        country(country) {}


const std::pair<double, double> &Airport::getPositionInfo() const {
    return positionInfo;
}

const std::string &Airport::getCode() const {
    return code;
}

const std::string &Airport::getName() const {
    return name;
}

const std::string &Airport::getCity() const {
    return city;
}

const std::string &Airport::getCountry() const {
    return country;
}

const std::vector<Flight> &Airport::getDestinations() const {
    return destinations;
}

bool Airport::isVisited() const {
    return visited;
}

void Airport::setVisited(bool value){
    visited = value;
}

int Airport::getIndegree() const {
    return indegree;
}

int Airport::setIndegree(int indegree) {
    return this->indegree = indegree;
}

bool Airport::addDestination(Flight &flight) {
    for (Flight f : destinations) {
        if (f.getDest() == flight.getDest())
            return false;
    }

    destinations.push_back(flight);
    return true;
}

std::pair<double, double> Airport::getInfo(){
    return positionInfo;
}

bool Airport::operator == (const Airport &p2) const {
    return (code==p2.code);
}
