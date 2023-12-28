#include "FlightManager.h"


void FlightManager::parseData(){
    std::cout << "Now begin";
    std::ifstream in;

    // Open the file using the provided path.
    std::cout << "Now airlines";
    in.open("../inputFiles/airlines.csv");
    if (!in.is_open()){
        std::cout << "Unable to open airlines.csv.\n";
        return;
    }
    processAirlines(in);
    in.close();

    std::cout << "Now airports";
    in.open("../inputFiles/airports.csv");
    if (!in.is_open()){
        std::cout << "Unable to open airports.csv.\n";
        return;
    }
    processAirports(in);
    in.close();

    std::cout << "Now flights";
    in.open("../inputFiles/flights.csv");
    if (!in.is_open()){
        std::cout << "Unable to open flights.csv.\n";
        return;
    }
    processFlights(in);
    in.close();
}

void FlightManager::processAirlines(std::ifstream &in){
    std::string line;
    getline(in,line);
    while(getline(in, line)) {
        std::istringstream s(line);
        std::string code, name, country, callsign;
        if (std::getline(s, code, ',') && std::getline(s, name, ',') && std::getline(s, callsign, ',') && std::getline(s, country, '\r')) {
            for (char& c : code) c = (char) tolower(c);
            for (char& c : name) c = (char) tolower(c);
            for (char& c : country) c = (char) tolower(c);
            for (char& c : callsign) c = (char) tolower(c);
            auto* airline = new Airline(code, name, country, callsign);

            airlineSet.insert(airline);
            airlineMap[code] = airline;

        } else {
            std::cerr << "Invalid line in the CSV file" << line << std::endl;
        }
    }

    // ToDo remover
    /*for (auto airline : airlineMap){
        cout << "airline with name " << airline.second->getName() << std::endl;
    }*/
}
void FlightManager::processAirports(std::ifstream &in){
    std::string line;
    getline(in,line);
    while (getline(in, line)) {
        std::istringstream s(line);
        std::string code, name, city, country, lat, longit;
        std::pair<double,double> position;

        if (std::getline(s, code, ',') && std::getline(s, name, ',') && std::getline(s, city, ',') && std::getline(s, country, ',') && std::getline(s, lat, ',') && std::getline(s, longit, '\r')) {
            position.first = std::stod(lat);
            position.second = std::stod(longit);
            for (char& c : code) c = (char) tolower(c);
            for (char& c : name) c = (char) tolower(c);
            for (char& c : city) c = (char) tolower(c);
            for (char& c : country) c = (char) tolower(c);
            auto* airport = new Airport(position, code, name, city, country);
            airportMap[code] = airport;

            if (!airportNetwork.addVertex(airport)){
                std::cout << "Error while adding vertex to graph.";
            }
        } else {
            std::cerr << "Invalid line in the CSV file" << line << std::endl;
        }
    }
    // ToDo remover
    /*for (auto airport : airportMap){
        cout << "Airport with code " << airport.second->getCode() << std::endl;
    }*/
}
void FlightManager::processFlights(std::ifstream &in){
    std::string line;
    getline(in, line);
    while (getline(in, line)) {
        std::istringstream s(line);
        std::string source, target, airlineCode;

        if (getline(s, source, ',') && getline(s, target, ',') && getline(s, airlineCode, '\r')) {
            for (char& c : source) c = (char) tolower(c);
            for (char& c : target) c = (char) tolower(c);
            for (char& c : airlineCode) c = (char) tolower(c);
            Airline* airline = airlineMap[airlineCode];
            Airport* sourceAirport = airportMap[source];
            Airport* targetAirport = airportMap[target];

            // ToDo Remover cout
            //cout << "Source is " << sourceAirport->getName() << " target is " << targetAirport->getName() << " and we are flying with " << airline->getName() << "\n";
            double distance = airportNetwork.calculateDistance(sourceAirport->getPositionInfo(), targetAirport->getPositionInfo());
            if (!airportNetwork.addEdge(sourceAirport, targetAirport, distance, airline)){
                std::cout << "Error while adding edge to graph.";
            }
        }
        // ToDo remover
        /*for (auto iDontKnowAnymore : this->airportNetwork.getVertexSet()){
            cout << "Airport with name " << iDontKnowAnymore->getInfo()->getName() << std::endl;
        }*/
    }
}


// 1
void FlightManager::printGlobalNumAirports(){
    // ToDo
}
void FlightManager::printGlobalNumFlights(){
    // ToDo
}


// 2
void FlightManager::printNumFlightsOutOfAirport(){
    // ToDo
}


// 3

/*void FlightManager::printNumFlightsCity(const std::string& cityName, const std::string& coutryName){

    * @brief Print the number of flights that a city has.
     *  @details The number of flights is considered to be out-degree (Flights that have this Airport as source)
     *  @details plus it's in-degree (Flights that have this Airport as destination).
     *  @details The Time Complexity should be O(1 + cityNameSize + coutryNameSize) however, if a city has more than one Airport then
     *  @details Time Complexity will be O(Number of Airports of that City + cityNameSize + coutryNameSize).
     *  @details Also, due to the use of an hashmap, in the worst case the Time Complexity can be O(n + cityNameSize + coutryNameSize)
     *  @details or even O(n + Number of Airports of that City + cityNameSize + coutryNameSize) where n is the size of the hashmap.
    *

    // All names should be lowercase to make searching easier.
    std::string cityNameDup = cityName;
    for (char &c: cityNameDup) c = (char) std::tolower(c);

    std::string coutryNameDup = coutryName;
    for (char &c: coutryNameDup) c = (char) std::tolower(c);

    // Get the unordered map and find the city.
    std::unordered_map<std::pair<std::string,std::string>, std::vector<Airport*>, PairHash> airports = airportNetwork.getCountryAirports();
    auto foundCityAirports = airports.find({cityNameDup, coutryNameDup});

    // Case where there is no city with the given name was found.
    if (foundCityAirports == airports.end()){
        std::cout << "No city named " << cityName << " of country " << coutryName << " exists.\n";
        return;
    }

    // Get total number of flights.
    unsigned long totalFlights = 0;
    for (Airport* airport : foundCityAirports->second){
        totalFlights += airport->getDestinations().size();
        totalFlights += airport->getIndegree();
    }

    std::cout << "The number of flights for " << cityName << ", " << coutryName << " is " << totalFlights << ".\n";
}*/

/** @brief Print the number of flights that a city has.
 *  @details The number of flights is calculated using a dfs approach. We use the dfs algorithm to visit every airport
 *  @details and check it's name and it's country. If these match then we add all outgoing flights to numberFlights
 *  @details so that when we reach the end we have the total amount of flights that a given city has.
 *  @details We also check if a given destination is the expected airport. If it is then we also add +1 because it also counts
 *  @details as a flight, incoming flights (in-degree).
 *  @details Time Complexity for this is O(V) + O(E) where V is the number of airports and E then number of edges.
 * */
void dfsAirport(Vertex<Airport*>* airport, unsigned long& numberFlights, const std::string& cityName, const std::string& coutryName);
void FlightManager::printNumFlightsCity(const std::string& cityName, const std::string& coutryName){
    unsigned long numberFlights = 0;

    // LowerCase Names.
    std::string cityNameDup = cityName;
    for (char &c: cityNameDup) c = (char) std::tolower(c);
    std::string coutryNameDup = coutryName;
    for (char &c: coutryNameDup) c = (char) std::tolower(c);

    for (Vertex<Airport*>* airport : airportNetwork.getVertexSet()){
        airport->setVisited(false);
    }

    for (Vertex<Airport*>* airport : airportNetwork.getVertexSet()){
        if (!airport->isVisited()){
            dfsAirport(airport, numberFlights, cityNameDup, coutryNameDup);
        }
    }

    std::cout << "The city " << cityName << " from " << coutryName;
    numberFlights == 0 ? std::cout << " has no flights.\n" : std::cout << " has " << numberFlights << " flights.\n";
}

void dfsAirport(Vertex<Airport*>* airport, unsigned long& numberFlights, const std::string& cityName, const std::string& coutryName){
    airport->setVisited(true);

    if (airport->getInfo()->getCity() == cityName && airport->getInfo()->getCountry() == coutryName){
        numberFlights += airport->getAdj().size(); // out-degree
    }

    for (const auto& flight : airport->getAdj()){

        auto destinationAirport = flight.getDest();

        if (destinationAirport->getInfo()->getCity() == cityName && destinationAirport->getInfo()->getCountry() == coutryName){
            numberFlights += 1; // in-degree
        }

        if (!destinationAirport->isVisited()){
            dfsAirport(destinationAirport, numberFlights, cityName, coutryName);
        }
    }
}

/** @brief Print the number of flights that an airline has.
 *  @details The number of flights is calculated using a dfs approach. We use the dfs algorithm to visit every airport
 *  @details and check it's edges (Flight). From here we verify if the any flight of this airport is of the airline we are looking for.
 *  @details If it is then we will increment the counter.
 *  @details Time Complexity for this is O(V) + O(E) where V is the number of airports and E then number of edges.
 * */
void dfsNumberFlights(Vertex<Airport*>* airport, int& numberFlights, const std::string& airlineCode);
void FlightManager::printNumFlightsAirline(const std::string& airlineCode){
    int numberFlights = 0;

    for (Vertex<Airport*>* airport : airportNetwork.getVertexSet()){
        airport->setVisited(false);
    }

    for (Vertex<Airport*>* airport : airportNetwork.getVertexSet()){
        if (!airport->isVisited()){
            dfsNumberFlights(airport, numberFlights, airlineCode);
        }
    }

    std::cout << "Airline with code " << airlineCode;
    numberFlights == 0 ? std::cout << " has no flights.\n" : std::cout << " has " << numberFlights << " flights.\n";
}

void dfsNumberFlights(Vertex<Airport*>* airport, int& numberFlights, const std::string& airlineCode){
    airport->setVisited(true);

    for (const Edge<Airport*>& flight : airport->getAdj()){
        if (flight.getWeight2()->getCode() == airlineCode){
            numberFlights++;
        }

        auto destinationAirport = flight.getDest();
        if (!destinationAirport->isVisited()){
            dfsNumberFlights(destinationAirport, numberFlights, airlineCode);
        }
    }
}


// 4
void FlightManager::printNumCountriesFromAirport(std::string airport_name){
    // ToDo
    std::cout << airport_name;
    // algorithm:
    // 1. traverse adjacency list of airport
    // 2. print all country names of the list
}

/** @brief Print the number of airports, countries or cities from a given airport.
 *  @details From a given airport code we will check it's neighboring vertices while also keeping track of the countries, cities and airports that
 *  @details were visited for those cases where there are two cities with the same name or a single city has many airports.
 *  @details Time Complexity for this is O(V) + O(E)*O(n) (lookup for vertex + iterating over edges * number of cities (or countries) that were already visited.)
 * */
void FlightManager::printNumDestinations(const std::string& airportCode,  std::vector<int> filters){

    string dupCode = airportCode;
    for (char& c : dupCode) c = (char) tolower(c);

    Airport* airport = this->airportMap[dupCode];

    if (airport == nullptr){
        std::cout << "No Airport with the code" << airportCode << "was found\n";
        return;
    }

    bool containsOne = std::find(filters.begin(), filters.end(), 1) != filters.end();
    bool containsTwo = std::find(filters.begin(), filters.end(), 2) != filters.end();
    bool containsThree = std::find(filters.begin(), filters.end(), 3) != filters.end();

    unsigned long reachableAirports = 0;
    unsigned long reachableCountries = 0;
    unsigned long reachableCities = 0;
    Vertex<Airport*>* airportSource = airportNetwork.findVertex(airport);
    vector<string> countries;
    vector<string> cities;

    for (Edge<Airport*> flight : airportSource->getAdj()){
        Vertex<Airport*>* destination = flight.getDest();

        if (!destination->isVisited()){
            reachableAirports++;
            if (std::find(countries.begin(), countries.end(), destination->getInfo()->getCountry()) == countries.end()){
                countries.push_back(destination->getInfo()->getCountry());
                reachableCountries++;
            }
            if (std::find(cities.begin(), cities.end(), destination->getInfo()->getCity()) == cities.end()){
                countries.push_back(destination->getInfo()->getCity());
                reachableCities++;
            }
            destination->setVisited(true);
        }
    }

    if (containsOne){
        std::cout << "The number of reachable Airports from Airport with code "<< airportCode << " is " << reachableAirports << ".\n";
    }
    if (containsTwo){
        std::cout << "The number of reachable Countries from Airport with code "<< airportCode << " is " << reachableCountries << ".\n";
    }
    if (containsThree){
        std::cout << "The number of reachable Cities from Airport with code "<< airportCode << " is " << reachableCities << ".\n";
    }
}

// 5
int numAirportsReachableBFS(const Graph<Airport> *airport_network, const Airport &source, int x);
void FlightManager::printNumReachableDests(std::string airport_code, int x){
    // ToDo
    std::cout << airport_code;
    // algorithm:
    // 1. bfs for all distances until x
    // 2. count number of airports, cities, countries (separately)
    // 3. print counts
}

int numAirportsReachableBFS(const Graph<Airport> *airport_network, const Airport &source, int x) {
    int count = 0;
    auto vertex = airport_network->findVertex(source);

    for (auto& a : airport_network->getVertexSet()) a->setVisited(false);

    if (vertex == nullptr) return count;

    std::queue<Vertex<Airport>*> q;
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

            for (auto& e : v->getAdj()){
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


// 6
void FlightManager::printMaxTrip(){
    // ToDo
}


// 7
void FlightManager::printTopKAirport(int k){
    // ToDo
    for (Vertex<Airport*>* airport : airportNetwork.getVertexSet()){
        // DEBUG
        std::cout << airport->getAdj().size();
        std::cout << "AAA";
    }
    // algorithm:
    // 1. k is the number of times a max is skipped
    // 2. Find the next max until k is 0
    // 3. print the k-th airport
}


// 8
void FlightManager::printEssentialAirports(){
    // ToDo
}

void FlightManager::testingCalculateDistance() {
    double lat1,lat2,long1,long2;
    std::cout << "lat 1 = "; std::cin >> lat1;
    std::cout << "lat 2 = "; std::cin >> lat2;
    std::cout << "long 1 = "; std::cin >> long1;
    std::cout << "long 2 = "; std::cin >> long2;

    double res = airportNetwork.calculateDistance(std::pair<double, double>(lat1, long1), std::pair<double, double>(lat2, long2));
    std::cout << "distance = " << res;
}

FlightManager::FlightManager() = default;
