#include "responses.h"

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if(r.buses.size() == 0)
        return os << "No stop";
    for (const string& bus : r.buses)
        cout << bus << " ";
    return cout;
}

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    if(r.stops.size() == 0)
        return os << "No bus";
    for (int i = 0; i < r.stops.size(); i++) {
        const string& stop = r.stops[i];
        cout << "Stop " << stop << ": ";
        if (r.interchanges.count(stop) == 0) {
            cout << "no interchange";
        } else {
            for (const string& other_bus : r.interchanges.at(stop)) {
                //if (bus != other_bus)
                    cout << other_bus << " ";
            }
        }
        if(i + 1 < r.stops.size()) cout << endl;
    }
    return cout;
}

ostream& operator << (ostream& os, const AllBusesResponse &r) {
    if (r.buses_to_stops.empty())
        return cout << "No buses";
    auto iLine = 0;
    for(const auto& bus_item : r.buses_to_stops) {        
        cout << "Bus " << bus_item.first << ": ";
        for (const string& stop : bus_item.second) {
            cout << stop << " ";
        }
        if(iLine++ + 1 < r.buses_to_stops.size())
          cout << endl;
    }
    return os;
}
