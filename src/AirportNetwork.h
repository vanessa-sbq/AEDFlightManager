//
// Created by vascocosta on 12/26/23.
//

#ifndef AEDFLIGHTMANAGER_AIRPORTNETWORK_H
#define AEDFLIGHTMANAGER_AIRPORTNETWORK_H

#include "Airport.h"

class AirportNetwork {
    std::vector<Airport*> airports;

public:
    Airport *findAirport(const std::pair<double, double> &info) const;
    bool addAirport(const std::pair<double,double> &info,
                    std::string code,
                    std::string name,
                    std::string city,
                    std::string country);

    bool addFlight(const Airport* origin, const Airport* destination, double distance, Airline &airline);
    double calculateDistance(const std::pair<double, double> p1, const std::pair<double, double> p2);
    std::vector<Airport*> getAirports();
};


#endif //AEDFLIGHTMANAGER_AIRPORTNETWORK_H
