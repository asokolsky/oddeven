#include "bus_manager.h"

void BusManager::AddBus(const string& bus, const vector<string>& stops) {
    buses_to_stops[bus] = stops;
    for (const string& stop : stops)
        stops_to_buses[stop].push_back(bus);
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
    BusesForStopResponse res;
    if (stops_to_buses.count(stop) != 0)
        res.buses = stops_to_buses.at(stop);
    return res;
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
    StopsForBusResponse res;  
    if (buses_to_stops.count(bus) != 0) {
    for (const string& stop : buses_to_stops.at(bus)) {
        res.stops.push_back(stop);
        if (stops_to_buses.count(stop) > 0 && stops_to_buses.at(stop).size() > 1)
        for (const string& other_bus : stops_to_buses.at(stop))
            if (bus != other_bus)
            res.interchanges[stop].push_back(other_bus);
    }
    }
    return res;
}

AllBusesResponse BusManager::GetAllBuses() const {
    AllBusesResponse res;
    res.buses_to_stops = buses_to_stops;
    return res;
}

