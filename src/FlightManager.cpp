#include <algorithm>
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
/**
 * @brief Prints the number of countries that an airport flies to
 * @details Time complexity: O(V + E), where V is the number of airports and E is the number of edges of an airport
 */
void FlightManager::printNumCountriesAirport(std::string airportCode){
    Airport* source = airportMap[airportCode];
    auto vertex = airportNetwork.findVertex(source);
    set<std::string> res;
    for (Edge<Airport*> e : vertex->getAdj()) res.insert(e.getDest()->getInfo()->getCountry());
    if (res.size() == 1) cout << "There are direct flights to 1 country from the airport with code " << airportCode << ".";
    else cout << "There are direct flights to " << res.size() << " different countries from the airport with code " << airportCode << ".";
}
// 4
void FlightManager::printNumCountriesCity(std::string city) {
    set<std::string> res; // Different countries
    vector<Airport*> airportsInCity;  // A city may have multiple airports
    auto it = airportMap.begin();
    for (it = airportMap.begin(); it != airportMap.end(); it++){
        if (it->second->getCity() == city) airportsInCity.push_back(it->second);
    }
    for (Airport* airport : airportsInCity){
        auto vertex = airportNetwork.findVertex(airport);
        for (Edge<Airport*> e : vertex->getAdj()) res.insert(e.getDest()->getInfo()->getCountry());
    }
    if (res.size() == 1) cout << "There are direct flights to 1 country from " << city << ".";
    else cout << "There are direct flights to " << res.size() << " different countries from " << city << ".";
}


void FlightManager::printNumDestinations(const std::string& airportName){
    
}


// 5
/**
 * @brief Prints the number of reachable destinations (airports, cities or countries) in a maximum number of X stops (lay-overs)
 * @details Time complexity: O(V + E)
 */
void FlightManager::printNumReachableX(const std::string& airport_code, int x, int funcNum){
    x++; // x stops means that there are x + 1 levels of destinations
    Airport* source = airportMap[airport_code];

    std::vector<std::string> res;

    auto vertex = airportNetwork.findVertex(source);

    for (auto& a : airportNetwork.getVertexSet()) a->setVisited(false);

    if (vertex == nullptr){
        std::cout << "The airport with the code " << airport_code << " doesn't exist.";
        return;
    }

    std::queue<Vertex<Airport*>*> q;
    q.push(vertex);
    vertex->setVisited(true);
    int level = 0;
    while (!q.empty() && level < x + 1){
        int size = q.size();
        for (int i = 0; i < size; i++){
            auto v = q.front();
            q.pop();
            if (level <= x && level > 0) {
                if (funcNum == 0) res.push_back(v->getInfo()->getCode());
                else if (funcNum == 1) res.push_back(v->getInfo()->getCity());
                else if (funcNum == 2) res.push_back(v->getInfo()->getCountry());
            }

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
    if (funcNum == 0) std::cout << "There are " << res.size() << " airport destinations with a maximum of " << x-1 << " layovers.";
    else if (funcNum == 1) std::cout << "There are " << res.size() << " city destinations with a maximum of " << x-1 << " layovers.";
    else if (funcNum == 2) std::cout << "There are " << res.size() << " country destinations with a maximum of " << x-1 << " layovers.";
}

// 6
void FlightManager::printMaxTrip(){
    // ToDo
}


// 7
bool compPairs(const std::pair<int, Airport*>& p1, const std::pair<int, Airport*>& p2){
    return p1.first > p2.first;
}
// ToDo: make this more efficient
void FlightManager::printTopKAirport(int k){
    int a = k;
    std::vector<std::pair<int, Airport*>> res;
    std::vector<std::pair<int, Airport*>> airportTraffic;
    for (auto vertex : airportNetwork.getVertexSet()){
        int numFlights = numberOfFlights(vertex);
        airportTraffic.push_back(make_pair(numFlights, vertex->getInfo()));
    }


    std::sort(airportTraffic.begin(), airportTraffic.end(), compPairs);

    if (a < 1 || a >= airportTraffic.size()){
        cout << "k is invalid!";
        return;
    }
    // ToDo: try to implement this correctly
    /*if (airportTraffic.empty()) cout << "There are no airports!";
    bool different = true;
    std::pair<int, Airport*>& previous = airportTraffic[0];
    k--;
    for (auto it = airportTraffic.begin(); it != airportTraffic.end(); it++){
        if (previous.first == it->first) different = false;
        else different = true;
        cout << "different: " << different << " number:" << it->first << std::endl;
        if (k == 0) res.push_back(*it);

        if (different){
            k--;
            if (k <= 0) break;
        }
        previous = *it;
    }*/

    cout << "The top " << a << " airport is " << airportTraffic[a-1].second->getCode() << " with " << airportTraffic[a-1].first << " flights.\n";
}
int FlightManager::numberOfFlights(Vertex<Airport*>* airport){  // auxiliary function
    int numFlights = 0;

    // number of outgoing flights
    numFlights = airport->getAdj().size();

    // number of incoming flights
    for (auto v : airportNetwork.getVertexSet()){
        for (auto e : v->getAdj()){
            if (e.getDest()->getInfo()->getCode() == airport->getInfo()->getCode()) numFlights++;
        }
    }

    return numFlights;
}


// 8
void FlightManager::printEssentialAirports(){
    // ToDo
}


// 9
vector<Airport*> shortestPath(Vertex<Airport*>* start, Vertex<Airport*>* end, const vector<Airline *>& airlines);
void FlightManager::printFlightOptionAirlineFiltered(const string& sourceCode, const string& destCode, const string& filteredAirlines) {
    // Extract the airline codes from the user input
    vector<string> airlineCodes;
    string airlineCode;
    istringstream ss(filteredAirlines);
    while (std::getline(ss, airlineCode, ',')) {
        airlineCode.erase(std::remove(airlineCode.begin(), airlineCode.end(), ' '), airlineCode.end());
        cout << airlineCode << endl;
        airlineCodes.push_back(airlineCode);
    }
    vector<Airline *> airlines;
    for (string airlineCode: airlineCodes) {      // Find the airlines
        try {
            airlines.push_back(airlineMap.at(airlineCode));
        } catch(const std::out_of_range& e) {
            continue;   // Invalid airlines are ignored
        }
    }

    // Find the source and destination airports
    Airport* source;
    Airport* dest;
    try{
        source = airportMap.at(sourceCode);
        dest = airportMap.at(destCode);
    } catch (const std::out_of_range& e) {
        cout << "The source or destination airports don't exist!\n";
        return;
    }
    Vertex<Airport*>* vertexSource = airportNetwork.findVertex(source);
    Vertex<Airport*>* vertexDest = airportNetwork.findVertex(dest);
    if (vertexSource == nullptr || vertexDest == nullptr) {
        std::cout << "The source or destination airports don't exist!\n";
        return;
    }

    // Set all nodes to unvisited
    for (auto v : airportNetwork.getVertexSet()) v->setVisited(false);

    vector<Airport*> shortest = shortestPath(vertexSource, vertexDest, airlines);
    if (shortest.size() == 0) {
        cout << "The destination is not reachable with this configuration!";
        return;
    }
    for (int i = 0; i < shortest.size() - 1; i++){
        cout << shortest[i]->getCode() << " -> ";
    }
    cout << shortest[shortest.size() - 1]->getCode();
}
bool airlineInFilter(Edge<Airport*> edge, vector<Airline*> filteredAirlines){
    for (Airline* airline : filteredAirlines){
        if (edge.getWeight2()->getCode() == airline->getCode()) return true;
    }
    return false;
}
vector<Airport*> shortestPath(Vertex<Airport*>* start, Vertex<Airport*>* end, const vector<Airline*>& airlines) {
    queue<Vertex<Airport*>*> q;
    unordered_set<Airport*> visited;
    unordered_map<Vertex<Airport*>*, Vertex<Airport*>*> parent;

    // Start BFS
    q.push(start);
    visited.insert(start->getInfo());

    // BFS Iteration
    while (!q.empty()) {
        Vertex<Airport*>* current = q.front();
        q.pop();

        for (Edge<Airport*> edge : current->getAdj()) {
            if (airlineInFilter(edge, airlines)) {  // Ignore airlines that are not in filter
                Vertex<Airport *> *neighbor = edge.getDest();
                Airport *neighborInfo = neighbor->getInfo();
                if (visited.find(neighborInfo) == visited.end()) {
                    q.push(neighbor);
                    visited.insert(neighborInfo);
                    parent[neighbor] = current;

                    // Finish BFS if the destination is reached
                    if (neighbor == end) {
                        // Reconstruct Shortest Path
                        vector<Airport *> path;
                        while (parent.find(neighbor) != parent.end()) {
                            path.push_back(neighbor->getInfo());
                            neighbor = parent[neighbor];
                        }
                        path.push_back(start->getInfo());
                        reverse(path.begin(), path.end());
                        return path;
                    }
                }
            }
        }
    }

    // If the destination is not reachable from the start
    return vector<Airport*>();
}


// 9
void FlightManager::printFlightOptionMinimalAirlines(){

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
