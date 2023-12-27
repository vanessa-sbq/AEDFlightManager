//
// Created by vascocosta on 12/26/23.
//

#include "AirportNetwork.h"
#include <queue>

Airport *AirportNetwork::findAirport(const std::pair<double, double> &info) const {
    for (Airport *airport : airports) {
        if (airport->getPositionInfo() == info)
            return airport;
    }

    return nullptr;
}

bool AirportNetwork::addAirport(const std::pair<double, double> &info, std::string code, std::string name, std::string city,
                           std::string country) {
    if (findAirport(info) != nullptr)
        return false;

    airports.push_back(new Airport(info, code, name, city, country));
    return true;
}

std::vector<Airport*> AirportNetwork::getAirports() {
    return airports;
}

bool AirportNetwork::addFlight(const Airport *origin, const Airport *destination, double distance, Airline &airline) {
    Airport* src = findAirport(origin->getPositionInfo());
    Airport* dest = findAirport(destination->getPositionInfo());

    if (src == nullptr || dest == nullptr)
        return false;

    Flight f(dest, distance, airline);
    src->addDestination(f);
    return true;
}

double AirportNetwork::calculateDistance(const std::pair<double, double> p1, const std::pair<double, double> p2) {
    double distanceLatitudes = (p2.first - p1.first) * M_PI / 180.0;
    double distanceLongitudes = (p2.second - p1.second) * M_PI / 180.0;

    double lat1 = p1.first * M_PI / 180.0;
    double lat2 = p2.first * M_PI / 180.0;

    double a = pow(sin(distanceLatitudes / 2),2) +
               pow(sin(distanceLongitudes / 2),2) *
               cos(lat1) * cos(lat2);

    double rad = 6371;
    double c = 2 * asin(sqrt(a));

    return rad * c;
}

int AirportNetwork::numAirportsReachableBFS(const std::pair<double,double> &source, int x) {
    int count = 0;
    auto vertex = findAirport(source);

    for (auto& a : getAirports()) a->setVisited(false);

    if (vertex == nullptr) return count;

    std::queue<Airport*> q;
    q.push(vertex);
    vertex->setVisited(true);
    int level = 0;
    while (!q.empty() && level < x + 1){
        int size = q.size();
        for (int i = 0; i < size; i++){
            auto v = q.front();
            q.pop();
            // ToDo: distinguish between airports, cities and countries
            if (level <= x) count++;

            for (auto& e : v->getDestinations()){
                auto w = e.getDest();
                if (!w->isVisited()){
                    w->setVisited(true);
                    q.push(w);
                }
            }
        }
        level++;
    }
    return count;
}
