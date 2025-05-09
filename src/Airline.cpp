#include "Airline.h"

Airline::Airline(std::string code, std::string name, std::string country, std::string callsign)
        : code(code), name(name), country(country), callsign(callsign) {}

const std::string &Airline::getCode() const {
    return code;
}

bool Airline::operator<(const Airline &other) const {
    return code < other.code;
}

bool Airline::operator==(const Airline &other) const {
    return code == other.code;
}





