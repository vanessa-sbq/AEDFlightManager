//
// Created by vascocosta on 12/26/23.
//

#ifndef AEDFLIGHTMANAGER_FLIGHT_H
#define AEDFLIGHTMANAGER_FLIGHT_H


#include "Airport.h"
#include "Airline.h"

class Airport;
class Flight {

    Airport* dest;
    double distance;
    Airline airline;
public:
    Flight(Airport *airport, double distance,  Airline &airline);
    Airport *getDest() const;
    Airline getAirline() const;
    double getDistance() const;
    friend class Airport;
    friend class AirportNetwork;
};


#endif //AEDFLIGHTMANAGER_FLIGHT_H
