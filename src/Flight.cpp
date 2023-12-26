//
// Created by vascocosta on 12/26/23.
//

#include "Flight.h"

Flight::Flight(Airport* airport, double distance, Airline &airline) : dest(airport), distance(distance), airline(airline) {}

Airport *Flight::getDest() const {
    return dest;
}

double Flight::getDistance() const {
    return distance;
}



