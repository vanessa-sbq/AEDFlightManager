//
// Created by vascocosta on 12/26/23.
//

#ifndef AEDFLIGHTMANAGER_AIRPORTNETWORK_H
#define AEDFLIGHTMANAGER_AIRPORTNETWORK_H

#include <cmath>
#include <iostream>
#include <functional>
#include "Airport.h"

struct PairHash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

class AirportNetwork {
    std::vector<Airport*> airports;
    std::unordered_map<std::pair<std::string,std::string>, std::vector<Airport*>, PairHash> countryAirports;

public:
    Airport *findAirport(const std::pair<double, double> &info) const;
    bool addAirport(const std::pair<double,double> &info,
                    std::string code,
                    std::string name,
                    std::string city,
                    std::string country);

    bool addFlight(const Airport* origin, const Airport* destination, double distance, Airline &airline);
    double calculateDistance(const std::pair<double, double> p1, const std::pair<double, double> p2);

    std::unordered_map<std::pair<std::string,std::string>, std::vector<Airport*>, PairHash> getCountryAirports() const{
        return countryAirports;
    }
};

#endif //AEDFLIGHTMANAGER_AIRPORTNETWORK_H
