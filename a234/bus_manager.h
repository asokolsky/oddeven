#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "responses.h"

using namespace std;

class BusManager {
private:
    std::map<string, std::vector<std::string>> buses_to_stops;
    std::map<string, std::vector<std::string>> stops_to_buses;  
public:
    BusManager () {}

    void AddBus(const std::string& bus, const std::vector<std::string>& stops);
    BusesForStopResponse GetBusesForStop(const std::string& stop) const;
    StopsForBusResponse GetStopsForBus(const std::string& bus) const;
    AllBusesResponse GetAllBuses() const;
};
