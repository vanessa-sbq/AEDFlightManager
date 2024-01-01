#include <algorithm>
#include <map>
#include "FlightManager.h"
#include <set>
#include <climits>


void FlightManager::parseData(){
    std::ifstream in;

    // Open the file using the provided path.
    in.open("../inputFiles/airlines.csv");
    if (!in.is_open()){
        std::cout << "Unable to open airlines.csv.\n";
        return;
    }
    processAirlines(in);
    in.close();

    in.open("../inputFiles/airports.csv");
    if (!in.is_open()){
        std::cout << "Unable to open airports.csv.\n";
        return;
    }
    processAirports(in);
    in.close();

    in.open("../inputFiles/flights.csv");
    if (!in.is_open()){
        std::cout << "Unable to open flights.csv.\n";
        return;
    }
    processFlights(in);
    in.close();

    for (auto vertex : airportNetwork.getVertexSet()){
        for (auto edge : vertex->getAdj()) {
            edge.getDest()->setIndegree(edge.getDest()->getIndegree()+1);
        }
    }
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
            airlineMap[code] = airline;

        } else {
            std::cerr << "Invalid line in the CSV file" << line << std::endl;
        }
    }
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
            airportNameMap[name] = airport;
            pair<string, string> stringPair =std::make_pair(city, country);
            airportCityMap[stringPair].push_back(airport);

            if (!airportNetwork.addVertex(airport)){
                std::cout << "Error while adding vertex to graph.";
            }
        } else {
            std::cerr << "Invalid line in the CSV file" << line << std::endl;
        }
    }
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

            double distance = airportNetwork.calculateDistance(sourceAirport->getPositionInfo(), targetAirport->getPositionInfo());
            if (!airportNetwork.addEdge(sourceAirport, targetAirport, distance, airline)){
                std::cout << "Error while adding edge to graph.";
            }
        }
    }
}

void FlightManager::printGlobalNumAirports(){
    std::cout << "Number of Airports = " << airportMap.size() << '\n';
}

void FlightManager::printGlobalNumFlights(){
    int numFlights = 0;
    for (auto v : airportNetwork.getVertexSet()) v->setVisited(false);

    for (auto v : airportNetwork.getVertexSet()) {
        if (!v->isVisited()) {
            queue<Vertex<Airport*> *> q;
            q.push(v);
            v->setVisited(true);
            while (!q.empty()) {
                auto vertex = q.front();

                numFlights += vertex->getAdj().size();

                q.pop();
                for (auto & e : vertex->getAdj()) {
                    auto w = e.getDest();
                    if ( ! w->isVisited() ) {
                        q.push(w);
                        w->setVisited(true);
                    }
                }
            }
        }
    }

    std::cout << "Number of flights = " << numFlights << '\n';
}


// 2
void FlightManager::printNumFlightsOutOfAirport(){
    std::string airport;
    std::cout << "Airport code: ";
    std::cin >> airport;

    for (char &c : airport) c = char(tolower(c));

    Airport* air;
    try {
        air = airportMap.at(airport);
    } catch (std::out_of_range& ofr){
        std::cout << "Invalid airport code" << '\n';
        return;
    }

    auto v = airportNetwork.findVertex(air);
    if (v == NULL) {
        std::cout << "Invalid airport code" << '\n';
        return;
    }

    std::cout << "Number of flights out of " << airport << ": " << v->getAdj().size() <<'\n';

    std::set<std::string> airlines;
    for (Edge<Airport*> e : v->getAdj()) {
        airlines.insert(e.getWeight2()->getCode());
    }

    std::cout << "Number of airlines flying out of " << airport << ": " << airlines.size() << '\n';
}

// 3
/** @brief Print the number of flights that a city has.
 *  @details We visit every airport of the city and add it's in-degree plus it's out-degree.
 *  @details Time Complexity for this is (O(V) + O(E))*O(x) where V is the number of airports, E then number of edges
 *  @details and x is the number of airports of the city.
 * */
void FlightManager::printNumFlightsCity(const std::string& cityName, const std::string& coutryName){
    // LowerCase Names.
    std::string cityNameDup = cityName;
    for (char &c: cityNameDup) c = (char) std::tolower(c);
    std::string coutryNameDup = coutryName;
    for (char &c: coutryNameDup) c = (char) std::tolower(c);

    vector<Airport*> ap;
    try {
        ap = airportCityMap.at({cityNameDup, coutryNameDup});
    } catch (std::out_of_range& ofr) {
        std::cout << "No city name " << cityName << " from country " << coutryName << " was found\n";
        return;
    }

    unsigned long numberFlights = 0;
    for (auto airports : ap){
        Vertex<Airport*>* vertexAirport = airportNetwork.findVertex(airports);
        numberFlights += vertexAirport->getIndegree();
        numberFlights += vertexAirport->getAdj().size();
    }

    std::cout << "The city " << cityName << " from " << coutryName;
    numberFlights == 0 ? std::cout << " has no flights.\n" : std::cout << " has " << numberFlights << " flights.\n";
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
void FlightManager::printNumCountriesAirport(const std::string& airportCode){
    std::string airportCodeDup = airportCode;
    for (char& c : airportCodeDup) c = (char) tolower(c);

    Airport* source = airportMap[airportCodeDup];
    auto vertex = airportNetwork.findVertex(source);
    set<std::string> res;
    for (Edge<Airport*> e : vertex->getAdj()) res.insert(e.getDest()->getInfo()->getCountry());
    if (res.size() == 1) cout << "There are direct flights to 1 country from the airport with code " << airportCode << ".";
    else cout << "There are direct flights to " << res.size() << " different countries from the airport with code " << airportCode << ".";
}

// 4
/**
 * @brief Prints the number of countries that the airports in a city fly to
 * @details Time complexity: O(m * k), where m is the number of airports in the city and k is the average number of adjacent airports for each airport
 */
void FlightManager::printNumCountriesCity(const std::string& city, const std::string& country) {
    std::string cityDup = city;
    std::string countryDup = country;
    set<std::string> res; // Different countries
    vector<Airport*> airportsInCity;  // A city may have multiple airports

    for (char& c : cityDup) c = (char) tolower(c);
    for (char& c : countryDup) c = (char) tolower(c);

    try {
        airportsInCity = airportCityMap.at({cityDup, countryDup});
    } catch (std::out_of_range& ofr){
        cout << "No city with name " << city << " from " << country << " was found\n";
    }

    for (Airport* airport : airportsInCity){
        auto vertex = airportNetwork.findVertex(airport);
        for (Edge<Airport*> e : vertex->getAdj()) res.insert(e.getDest()->getInfo()->getCountry());
    }
    if (res.size() == 1) cout << "There are direct flights to 1 country from " << city << ".";
    else cout << "There are direct flights to " << res.size() << " different countries from " << city << ".";
}

/** @brief Print the number of airports, countries or cities from a given airport.
 *  @details From a given airport code we will check it's neighboring vertices while also keeping track of the countries, cities and airports that
 *  @details were visited for those cases where there are two cities with the same name or a single city has many airports.
 *  @details Time Complexity for this is O(V) + O(E)*O(n) (lookup for vertex + iterating over edges * number of cities (or countries) that were already visited.)
 * */
void FlightManager::printNumDestinationsForGivenAirport(const std::string& airportCode,  std::vector<int> filters){
    string dupCode = airportCode;
    for (char& c : dupCode) c = (char) tolower(c);

    Airport* airport;
    try {
        airport = this->airportMap[dupCode];
    } catch (out_of_range& ofr){
        std::cout << "No Airport with the code" << airportCode << "was found\n";
        return;
    }

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

    for (Vertex<Airport*>* airports: airportNetwork.getVertexSet()){
        airports->setVisited(false);
    }

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
/**
 * @brief Prints the number of reachable destinations (airports, cities or countries) in a maximum number of X stops (lay-overs)
 * @details Time complexity: O(V + E)
 */
void FlightManager::printNumReachableX(const std::string& airport_code, int x, int funcNum){
    x++; // x stops means that there are x + 1 levels of destinations
    Airport* source;
    try {
        source = airportMap.at(airport_code);
    } catch (std::out_of_range& ofr) {
        std::cout << "No airport with code " << airport_code << " was found\n";
        return;
    }
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
        int size = (int) q.size();
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
vector<Airport*> nodesAtDistanceBFS(Vertex<Airport*>*& sourceVertex, int& level) {
    vector<Airport*> targetAirports; // This is where we will store the reached airports
    queue<Vertex<Airport*>*> vertexQueue; // Queue for the vertexes that we have to process

    vertexQueue.push(sourceVertex); // Push the initial (source) vertex.
    sourceVertex->setVisited(true);
    level = 0; // Level starts at zero.

    while (!vertexQueue.empty()){


        targetAirports.clear(); // All the airports that were stored no longer are valid because there exists a higher level.
        unsigned long size = vertexQueue.size();

        // Process all elements of vertexQueue.
        // Note: We are limited by the size of the original vertexQueue -> size. This allows us to add even more
        // elements to the queue while still using it to finish the processing of the current level.
        for (unsigned long i = 0; i < size; i++){
            auto nextAirport = vertexQueue.front();

            targetAirports.push_back(nextAirport->getInfo()); // Add the element to the list
            vertexQueue.pop(); // Processing is still going to be done, but we can now remove it from the queue.

            // Get the flights from the current Airport.
            for (auto& flight : nextAirport->getAdj()){
                auto destinationAirport = flight.getDest();

                if (!destinationAirport->isVisited()){
                    destinationAirport->setVisited(true);
                    vertexQueue.push(destinationAirport);
                }

            }
        }
        if (!vertexQueue.empty()) level++; // We are on a new level.
    }
    // The bfs stops when we reach the maximum depth which corresponds to the maximum distance from a certain node.
    return targetAirports;
}

// 6
/**
 * @brief Prints the flights (source and destination) that have the most amount of stops.
 * @details Using a bfs approach we check for every single vertex what it's max depth is. In the case where the depth
 * @details is greater than the previous one we store the maximum depth as well as the source(s) and the destination(s) airports.
 * @details Time complexity: O(V * ( 2 * V + E)) where V is the number of vertexes (Airports) that the graph has and E
 * @details is the number of edges (flights) that an airport has.
 */
void FlightManager::printMaxTrip() {

    // This allows us to store the values for the source Airport and for the target Airports.
    unordered_map<string, vector<Airport*>> airportsLeveled;

    int maxLevel = 0;

    // Iterate through every single airport to find the ones that have the longer connections.
    for (auto& airportSource : airportNetwork.getVertexSet()){

        // Set all vertexes to unvisited
        for (auto& unvistVertex : airportNetwork.getVertexSet()){
            unvistVertex->setVisited(false);
        }

        // Reference to compare the level to check max(level, maxLevel)
        int level;
        // Get the final destinations
        vector<Airport*> finalDestinations = nodesAtDistanceBFS(airportSource, level);

        if (level > maxLevel){
            airportsLeveled.clear();
            airportsLeveled[airportSource->getInfo()->getCode()] = finalDestinations;
            maxLevel = level;
        } else {
            if (level == maxLevel){
                airportsLeveled[airportSource->getInfo()->getCode()] = finalDestinations;
            }
        }

    }

    // Print the results.
    cout << "The flights that have the most amount of stops are:\n";
    for (const auto& iter : airportsLeveled) {
        for (Airport* airport : iter.second){
            cout << "   From " << iter.first << " to "<< airport->getCode() << ".\n";
        }
    }
    cout << "Maximum distance: " << maxLevel << std::endl;

}

// 7
/**
 * @brief Prints the top-k airport with the greatest air traffic capacity, that is, with the greatest number of flights
 * @details Time complexity: O(V), where V is the number of vertices in the graph
 */
void FlightManager::printTopKAirport(int k){
    std::vector<std::pair<int, Airport*>> res;

    std::map< int, std::vector<Airport*> > airportTraffic;

    for (auto vertex : airportNetwork.getVertexSet()){
        unsigned long numFlights = 0;
        numFlights += vertex->getAdj().size();
        numFlights += vertex->getIndegree();
        airportTraffic[numFlights].push_back(vertex->getInfo());
    }

    if (k < 1 || k > airportTraffic.size()){
        cout << "k is invalid!";
        return;
    }

    auto iter = std::next(airportTraffic.begin(), airportTraffic.size() - k);

    if (iter->second.size() == 1) {
        cout << "The top " << k << " airport is " << iter->second[0]->getCode() << " with " << iter->first << " flights.\n";
        return;
    }
    cout << "The top " << k << " airports are:\n";
    for (auto airopp : iter->second){
       cout << airopp->getCode() << endl;
    }
    cout << "with " << iter->first << " flights.\n";
}

// 8
void FlightManager::printEssentialAirports(){
    unordered_set<Airport*> res;

    for (auto vertex : airportNetwork.getVertexSet()){
        vertex->setVisited(false);
        vertex->setProcessing(false);
    }

    stack<Airport*> s;
    int index = 1;
    for (auto v : airportNetwork.getVertexSet()){
        if (!v->isVisited()){
            airportNetwork.dfs_art(v, s, res, index);
        }
    }

    std::cout << "There are " << res.size() << " essential airports.\n";
}


vector<vector<Airport*>> elimDups(const vector<vector<Airport*>>& paths){
    vector<vector<Airport*>> uniquePaths;

    int min = paths[0].size();

    for (int i = 0; i < paths.size(); i++){
        if (paths[i].size() <= min) min = paths[i].size();
    }

    for (const vector<Airport*>& path : paths) {
        bool isDuplicate = false;
        if (path.size() != min) continue;
        for (const vector<Airport*>& uniquePath : uniquePaths) {
            if (path.size() != uniquePath.size()) continue;
            isDuplicate = true;
            for (size_t i = 0; i < path.size(); ++i) {
                if (path[i]->getCode() != uniquePath[i]->getCode()) {
                    isDuplicate = false;
                    break;
                }
            }
            if (isDuplicate) break;
        }
        if (!isDuplicate) uniquePaths.push_back(path);
    }
    return uniquePaths;

}
vector<vector<Airport*>> shortestPath(Vertex<Airport*>* start, Vertex<Airport*>* end, const vector<Airline *>& airlines, bool ignoreFilter);
/**
 * @brief Prints the best flights option with an optional airline filter
 * @details Time complexity: O(m * n * (V + E)), where m is the number of source vertices, n is the number of destination vertices and V + E is the complexity of the shortestPath function
 */
void FlightManager::printFlightOptionAirlineFiltered(vector<Vertex<Airport*>*> source , vector<Vertex<Airport*>*> dest, const string& filteredAirlines, bool ignoreFilter) {
    std::string filteredAirlinesDup = filteredAirlines;
    for (char& c : filteredAirlinesDup) c = (char) tolower(c);

    vector<Airline *> airlines;
    if (!ignoreFilter) {
        // Extract the airline codes from the user input
        vector<string> airlineCodes;
        string airlineCode;
        istringstream ss(filteredAirlinesDup);
        while (std::getline(ss, airlineCode, ',')) {
            airlineCode.erase(std::remove(airlineCode.begin(), airlineCode.end(), ' '), airlineCode.end());
            airlineCodes.push_back(airlineCode);
        }

        for (string airlineCode: airlineCodes) {      // Find the airlines
            try {
                airlines.push_back(airlineMap.at(airlineCode));
            } catch (const std::out_of_range &e) {
                continue;   // Invalid airlines are ignored
            }
        }
    }

    vector<vector<vector<Airport*>>> allShortest;
    for (Vertex<Airport*>* airportVertexSource : source){
        for (Vertex<Airport*>* airportVertexTarget : dest){
            for (auto v : airportNetwork.getVertexSet()) v->setVisited(false);
            allShortest.push_back(shortestPath(airportVertexSource, airportVertexTarget, airlines, ignoreFilter));
        }
    }

    if (allShortest.size() == 0) {
        cout << "The destination is not reachable with this configuration!";
        return;
    }

    vector<vector<vector<Airport*>>> allUniquePaths;
    for (vector<vector<Airport*>>& shortPaths : allShortest){
        vector<vector<Airport*>> uniquePaths = elimDups(shortPaths);
        allUniquePaths.push_back(uniquePaths);
    }


    if (allUniquePaths.size() != 0){
        cout << "The following options were found: \n";
        for (auto & allUniquePath : allUniquePaths){

            bool printHeader = true;

            for (auto& path : allUniquePath){

                if (printHeader){
                    cout << "\nDeparture from " << path.front()->getCode() << " to " << path.back()->getCode() << " includes the following flights:\n";
                    printHeader = false;
                }

                cout << "   ";
                for (int j = 0; j < path.size() - 1; j++) {
                    cout << path[j]->getCode() << " -> ";
                }
                cout << path[path.size() - 1]->getCode();
                cout << endl;
            }

        }
    } else {
        cout << "No options found.\n";
    }
}
bool airlineInFilter(Edge<Airport*> edge, const vector<Airline*>& filteredAirlines){
    for (Airline* airline : filteredAirlines){
        if (edge.getWeight2()->getCode() == airline->getCode()) return true;
    }
    return false;
}
/**
 * @brief BFS to compute the shortest path(s) between two vertices
 * @details Time complexity: O(V + E), where V is the number of vertices and E the number of edges
 * @return vector containing all the paths as vectors
 */
vector<vector<Airport*>> shortestPath(Vertex<Airport*>* start, Vertex<Airport*>* end, const vector<Airline*>& airlines, bool ignoreFilter) {
    vector<vector<Airport*>> res;
    queue<vector<Vertex<Airport*>*>> q;

    // Start BFS
    q.push({start});

    // BFS Iteration
    while (!q.empty()) {
        vector<Vertex<Airport*>*> path = q.front();
        q.pop();

        Vertex<Airport*>* current = path.back();

        // Mark the current node as visited
        current->setVisited(true);

        if (current == end) {
            vector<Airport*> airports;
            for (Vertex<Airport*>* vertex : path) {
                airports.push_back(vertex->getInfo());
            }
            res.push_back(airports);
        }

        for (Edge<Airport*> edge : current->getAdj()) {
            if (airlineInFilter(edge, airlines) || ignoreFilter) {  // Ignore airlines that are not in filter
                Vertex<Airport *> *neighbor = edge.getDest();

                // Only add neighbor to queue if it's not visited
                if (!neighbor->isVisited()) {
                    vector<Vertex<Airport*>*> newPath(path);
                    newPath.push_back(neighbor);
                    q.push(newPath);
                }
            }
        }
    }

    // If the destination is not reachable from the start
    return res;
}

struct bfsPath {
    std::vector<Vertex<Airport*>*> path;
    std::unordered_set<Airline*> airlines;
    int numAirlines = 0;
};
vector<bfsPath> bfsMinimalAirports(Vertex<Airport*> *v , Vertex<Airport*> *target) {
    std::queue<bfsPath> q;
    vector<bfsPath> res;

    bfsPath start;
    start.path.push_back(v);
    q.push(start);

    while (!q.empty()) {
        bfsPath currPath = q.front();
        q.pop();

        Vertex<Airport*> *currVertex = currPath.path.back();
        currVertex->setIndegree(currVertex->getIndegree()-1);

        if (currVertex == target) {
            res.push_back(currPath);
            if (currVertex->getIndegree() == 0) break;
            continue;
        }

        for (Edge<Airport*> e : currVertex->getAdj()) {
            Vertex<Airport*> *dest = e.getDest();
            if (dest->getIndegree() > 0) {
                bfsPath newPath(currPath);

                newPath.airlines.insert(e.getWeight2());
                if (currPath.airlines.size() != newPath.airlines.size()) newPath.numAirlines++;

                newPath.path.push_back(dest);

                q.push(newPath);
            }
        }
    }

    return res;
}

// 9
void FlightManager::printFlightOptionMinimalAirlines(vector<Vertex<Airport*>*> source , vector<Vertex<Airport*>*> dest){
    bfsPath best;
    best.numAirlines = INT_MAX;

    for (auto s : source) {
        for (auto d : dest) {
            for (Vertex<Airport*> *vertex : airportNetwork.getVertexSet()) {
                vertex->setIndegree(0);
            }
            for (Vertex<Airport*> *vertex : airportNetwork.getVertexSet()) {
                for (Edge<Airport*> e : vertex->getAdj()) {
                    e.getDest()->setIndegree(e.getDest()->getIndegree()+1);
                }
            }
            for (const bfsPath& p : bfsMinimalAirports(s, d)) {
                if (p.numAirlines < best.numAirlines) best = p;
            }
        }
    }

    std::cout << "This is the minimum amount of different airlines = " << best.numAirlines << "\n ROUTE ";
    for (Vertex<Airport*> *v : best.path) {
        std::cout << "|" << v->getInfo()->getCode();
    }
    std::cout << '\n';
}

/**
 * @brief Helper function.
 * @details It allows the user to input either an airport name, airport code, city name or
 * @details even geographical coordinates.
 * @details It's time complexity depends on what the combination the user chooses to use but assuming the worst possible
 * @details combination then it's O(4n).
 **/
pair<vector<Vertex<Airport*>*>, vector<Vertex<Airport*>*>> FlightManager::getConvertedVertexesFromUser(const string& input1, const string& input2, const string& input3, const string& input4, const string& input5, const string& input6, const string& radius){
    vector<Airport*> sourceAirports;
    vector<Airport*> targetAirports;
    string input1Dup = input1;
    string input3Dup = input3;
    string input5Dup = input5;
    string input6Dup = input6;
    int rad = 0;
    double latSource;
    double lonSource;
    double latTarget;
    double lonTarget;
    if (radius != "ignore") {
        try {
            rad = stoi(radius);
        } catch (std::invalid_argument &iv) {
            cout << "\nError while converting radius\n";
            return {};
        }
    }

    for (char& c : input1Dup) c = (char) tolower(c);
    for (char& c : input5Dup) c = (char) tolower(c);
    for (char& c : input6Dup) c = (char) tolower(c);

    try {
        if (input2 == "cityName") {
            sourceAirports = airportCityMap.at({input1Dup, input5Dup});
        } else if (input2 == "airportName") {
            sourceAirports.push_back(airportNameMap.at(input1Dup));
        } else if (input2 == "airportCode") {
            sourceAirports.push_back(airportMap.at(input1Dup));
        } else {
            try {
                latSource = stod(input1);
                lonSource = stod(input2);
            } catch (std::invalid_argument& inv) {
                cout << "\nError while converting coordinates for source airport.\n";
                return {};
            }

            for (const auto& airport : airportMap){
                double calculatedDistance = airportNetwork.calculateDistance(airport.second->getPositionInfo(), {latSource, lonSource});
                if (calculatedDistance <= rad){
                    sourceAirports.push_back(airport.second);
                }
            }

            if (sourceAirports.empty()){
                cout << "\nNo source airports found.\n";
                return {};
            }

        }
    } catch (std::out_of_range& ofr) {
        std::cout << "\nNo source airport with specified input value -> " << input1 << " <- was found.\n";
        return {};
    }

    for (char& c : input3Dup) c = (char) tolower(c);

    try {
        if (input4 == "cityName") {
            targetAirports = airportCityMap.at({input3Dup, input6Dup});
        } else if (input4 == "airportName") {
            targetAirports.push_back(airportNameMap.at(input3Dup));
        } else if (input4 == "airportCode"){
            targetAirports.push_back(airportMap.at(input3Dup)); // code used
        } else {
            try {
                latTarget = stod(input3);
                lonTarget = stod(input4);
            } catch (std::invalid_argument& inv) {
                cout << "\nError while converting coordinates for target airport.\n";
                return {};
            }

            for (const auto& airport : airportMap){
                double calculatedDistance = airportNetwork.calculateDistance(airport.second->getPositionInfo(), {latTarget, lonTarget});
                if (calculatedDistance <= rad){
                    targetAirports.push_back(airport.second);
                }
            }

            if (targetAirports.empty()){
                cout << "\nNo target airports found.\n";
                return {};
            }
        }
    } catch (std::out_of_range& ofr){
        std::cout << "\nNo target airport with specified input value -> " << input3 << " <- was found.\n";
        return {};
    }

    vector<vector<Airport*>> voyages;
    vector<Vertex<Airport*>*> sourceVertex;
    vector<Vertex<Airport*>*> targetVertex;

    for (Airport* source : sourceAirports){
        sourceVertex.push_back(airportNetwork.findVertex(source));
    }

    for (Airport* target : targetAirports){
        targetVertex.push_back(airportNetwork.findVertex(target));
    }

    return {sourceVertex, targetVertex};

}

FlightManager::FlightManager() = default;
