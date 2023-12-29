#include "Airport.h"

#include <utility>

Airport::Airport(const std::pair<double, double> p,
                 std::string code,
                 std::string name,
                 std::string city,
                 std::string country) :
        positionInfo(p),
        code(std::move(code)),
        name(std::move(name)),
        city(std::move(city)),
        country(std::move(country)) {}


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

bool Airport::operator == (const Airport &p2) const {
    return (code==p2.code);
}

bool Airport::operator<(const Airport &p2) const {
    return code < p2.code;
}
