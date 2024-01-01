#ifndef AEDFLIGHTMANAGER_AIRLINE_H
#define AEDFLIGHTMANAGER_AIRLINE_H



#include <string>

/**@brief Represents an airline.*/
class Airline {
    std::string code;
    std::string name;
    std::string callsign;
    std::string country;

public:
    Airline(std::string code, std::string name, std::string country, std::string callsign = "_");

    const std::string &getCode() const;
    const std::string &getName() const;
    const std::string &getCallsign() const;
    const std::string &getCountry() const;

    bool operator<(const Airline &other) const;
    bool operator==(const Airline &other) const;

};

struct HashFunction {
    size_t operator()(const Airline *airline) const {
        return std::hash<std::string>()(airline->getCode());
    };
};
#endif //AEDFLIGHTMANAGER_AIRLINE_H
