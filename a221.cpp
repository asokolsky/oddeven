#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <cassert>

using namespace std;

/**
Как будет тестироваться ваша программа

Автоматическая проверяющая система заменит в вашей программе функцию main на ту, которая дана вам в файле starter.cpp, 
скомпилирует получившийся файл и прогонит на тестах для задачи «Автобусные остановки — 1».

Условие задачи «Автобусные остановки — 1»

Реализуйте систему хранения автобусных маршрутов. Вам нужно обрабатывать следующие запросы:

    NEW_BUS bus stop_count stop1 stop2 ... — добавить маршрут автобуса с названием bus и stop_count остановками с названиями stop1, stop2, ...
    BUSES_FOR_STOP stop — вывести названия всех маршрутов автобуса, проходящих через остановку stop.
    STOPS_FOR_BUS bus — вывести названия всех остановок маршрута bus со списком автобусов, на которые можно пересесть на каждой из остановок.
    ALL_BUSES — вывести список всех маршрутов с остановками.

Формат ввода

В первой строке ввода содержится количество запросов Q, затем в Q строках следуют описания запросов.

Гарантируется, что все названия маршрутов и остановок состоят лишь из латинских букв, цифр и знаков подчёркивания.

Для каждого запроса NEW_BUS bus stop_count stop1 stop2 ... гарантируется, что маршрут bus отсутствует, количество остановок больше 0,
а после числа stop_count следует именно такое количество названий остановок, причём все названия в каждом списке различны.
Формат вывода

Для каждого запроса, кроме NEW_BUS, выведите соответствующий ответ на него:

    На запрос BUSES_FOR_STOP stop выведите через пробел список автобусов, проезжающих через эту остановку, в том порядке,
    в котором они создавались командами NEW_BUS. Если остановка stop не существует, выведите No stop.
    На запрос STOPS_FOR_BUS bus выведите описания остановок маршрута bus в отдельных строках в том порядке, в котором они
    были заданы в соответствующей команде NEW_BUS. Описание каждой остановки stop должно иметь вид Stop stop: bus1 bus2 ...,
    где bus1 bus2 ... — список автобусов, проезжающих через остановку stop, в порядке, в котором они создавались командами NEW_BUS, 
    за исключением исходного маршрута bus. Если через остановку stop не проезжает ни один автобус, кроме bus, вместо списка автобусов
    для неё выведите no interchange. Если маршрут bus не существует, выведите No bus.
    На запрос ALL_BUSES выведите описания всех автобусов в алфавитном порядке. Описание каждого маршрута bus должно иметь вид
    Bus bus: stop1 stop2 ..., где stop1 stop2 ... — список остановок автобуса bus в порядке, в котором они были заданы в
    соответствующей команде NEW_BUS. Если автобусы отсутствуют, выведите No buses.

Предупреждение

Условие задачи выше содержит много важных деталей. Если вы не уверены в том, что не упустили ни одной, перечитайте условие ещё раз.
Пример

Ввод
10
ALL_BUSES
BUSES_FOR_STOP Marushkino
STOPS_FOR_BUS 32K
NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo
NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo
BUSES_FOR_STOP Vnukovo
NEW_BUS 950 6 Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo
NEW_BUS 272 4 Vnukovo Moskovsky Rumyantsevo Troparyovo
STOPS_FOR_BUS 272
ALL_BUSES

Вывод
No buses
No stop
No bus
32 32K
Stop Vnukovo: 32 32K 950
Stop Moskovsky: no interchange
Stop Rumyantsevo: no interchange
Stop Troparyovo: 950
Bus 272: Vnukovo Moskovsky Rumyantsevo Troparyovo
Bus 32: Tolstopaltsevo Marushkino Vnukovo
Bus 32K: Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo
Bus 950: Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo

 */

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
    // Реализуйте эту функцию
    string operation_code;
    cin >> operation_code;
    if (operation_code == "NEW_BUS") {
        q.type = QueryType::NewBus;
        cin >> q.bus;
        int stop_count;
        cin >> stop_count;
        q.stops.resize(stop_count);
        for (string& stop : q.stops) {
            cin >> stop;
            //stops_to_buses[stop].push_back(bus);
        }
    } else if (operation_code == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        cin >> q.stop;
    } else if (operation_code == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        cin >> q.bus;
    } else if (operation_code == "ALL_BUSES") {
        q.type = QueryType::AllBuses;
    }
    return is;
}

struct BusesForStopResponse {
  vector <string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if(r.buses.size() == 0)
        return os << "No stop";
    for (const string& bus : r.buses)
        cout << bus << " ";
    return cout;
}

struct StopsForBusResponse {
  vector <string> stops;
  map<string, vector<string>> interchanges;
};

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

struct AllBusesResponse {
  map<string, vector<string>> buses_to_stops;
};

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

class BusManager {
private:
    map<string, vector<string>> buses_to_stops;
    map<string, vector<string>> stops_to_buses;  
public:
    BusManager () {}

    void AddBus(const string& bus, const vector<string>& stops) {
        buses_to_stops[bus] = stops;
        for (const string& stop : stops)
            stops_to_buses[stop].push_back(bus);
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        BusesForStopResponse res;
        if (stops_to_buses.count(stop) != 0)
            res.buses = stops_to_buses.at(stop);
        return res;
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
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

    AllBusesResponse GetAllBuses() const {
        AllBusesResponse res;
        res.buses_to_stops = buses_to_stops;
        return res;
    }
};

/*
int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }
  return 0;
}
*/
/*
int main() {
  int q;
  cin >> q;

  map<string, vector<string>> buses_to_stops, stops_to_buses;

  for (int i = 0; i < q; ++i) {
    string operation_code;
    cin >> operation_code;

    if (operation_code == "NEW_BUS") {

      string bus;
      cin >> bus;
      int stop_count;
      cin >> stop_count;
      vector<string>& stops = buses_to_stops[bus];
      stops.resize(stop_count);
      for (string& stop : stops) {
        cin >> stop;
        stops_to_buses[stop].push_back(bus);
      }

    } else if (operation_code == "BUSES_FOR_STOP") {

      string stop;
      cin >> stop;
      if (stops_to_buses.count(stop) == 0) {
        cout << "No stop" << endl;
      } else {
        for (const string& bus : stops_to_buses[stop]) {
          cout << bus << " ";
        }
        cout << endl;
      }

    } else if (operation_code == "STOPS_FOR_BUS") {

      string bus;
      cin >> bus;
      if (buses_to_stops.count(bus) == 0) {
        cout << "No bus" << endl;
      } else {
        for (const string& stop : buses_to_stops[bus]) {
          cout << "Stop " << stop << ": ";
          if (stops_to_buses[stop].size() == 1) {
            cout << "no interchange";
          } else {
            for (const string& other_bus : stops_to_buses[stop]) {
              if (bus != other_bus) {
                cout << other_bus << " ";
              }
            }
          }
          cout << endl;
        }
      }

    } else if (operation_code == "ALL_BUSES") {

      if (buses_to_stops.empty()) {
        cout << "No buses" << endl;
      } else {
        for (const auto& bus_item : buses_to_stops) {
          cout << "Bus " << bus_item.first << ": ";
          for (const string& stop : bus_item.second) {
            cout << stop << " ";
          }
          cout << endl;
        }
      }

    }
  }

  return 0;
}
*/

/*
NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo
NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo
NEW_BUS 950 6 Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo
NEW_BUS 272 4 Vnukovo Moskovsky Rumyantsevo Troparyovo
STOPS_FOR_BUS 272
ALL_BUSES
*/
