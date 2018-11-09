#include <iostream>
#include <map>
#include <string>
#include <vector>


using namespace std;

/**
 * Реализуйте систему хранения автобусных маршрутов. Вам нужно обрабатывать следующие запросы:

    NEW_BUS bus stop_count stop1 stop2 ... — добавить маршрут автобуса с названием bus и stop_count остановками с названиями stop1, stop2, ...
    BUSES_FOR_STOP stop — вывести названия всех маршрутов автобуса, проходящих через остановку stop.
    STOPS_FOR_BUS bus — вывести названия всех остановок маршрута bus со списком автобусов, на которые можно пересесть на каждой из остановок.
    ALL_BUSES — вывести список всех маршрутов с остановками.
 * 
 */
map <string /* route */, vector <string> /* stops */> route2stops;
map <string /* stop */, vector <string> /* routes */> stop2routes;

void dump(vector <string> &strs)
{
  for(int i = 0; i < strs.size(); ++i)
    cout << strs[i] << " ";
  cout << endl;
}

void add_route_stop(string &route, string &stop)
{
  route2stops[route].push_back(stop);
  stop2routes[stop].push_back(route);
}

/**
    На запрос BUSES_FOR_STOP stop выведите через пробел список автобусов, проезжающих через эту остановку, 
    в том порядке, в котором они создавались командами NEW_BUS. 
    Если остановка stop не существует, выведите No stop.
 */
void busses_for_stop(string &stop)
{
  if(stop2routes.count(stop) == 0)
    cout << "No stop" << endl;
  else
    dump(stop2routes[stop]);
}

/**
    На запрос STOPS_FOR_BUS bus выведите описания остановок маршрута bus в отдельных строках в том порядке, 
    в котором они были заданы в соответствующей команде NEW_BUS. 
    Описание каждой остановки stop должно иметь вид Stop stop: bus1 bus2 ..., 
    где bus1 bus2 ... — список автобусов, проезжающих через остановку stop, в порядке, 
    в котором они создавались командами NEW_BUS, за исключением исходного маршрута bus. 
    Если через остановку stop не проезжает ни один автобус, кроме bus, 
    вместо списка автобусов для неё выведите no interchange. 
    Если маршрут bus не существует, выведите No bus.
 */
void stops_for_bus(string &route)
{
  if(route2stops.count(route) == 0) {
    cout << "No bus" << endl;
    return;
  }
  vector <string> &stops = route2stops[route];
  for(int i = 0; i < stops.size(); ++i)
  {
    string &stop = stops[i];
    cout << "Stop " << stop << ": ";
    vector <string> &stopRoutes = stop2routes[stop];
    if(stopRoutes.size() <= 1)
      cout << "no interchange";
    else 
      for(int i = 0; i < stopRoutes.size(); ++i)
        if(stopRoutes[i] == route)
          continue;
        else
          cout << stopRoutes[i] << " ";
    cout << endl;
  }
}
/**
    На запрос ALL_BUSES выведите описания всех автобусов в алфавитном порядке. 
    Описание каждого маршрута bus должно иметь вид Bus bus: stop1 stop2 ..., 
    где stop1 stop2 ... — список остановок автобуса bus в порядке, в котором они были заданы в соответствующей команде NEW_BUS. 
    Если автобусы отсутствуют, выведите No buses.
 */
void all_buses()
{
  if(route2stops.size() == 0)
    cout << "No buses" << endl;
  else 
    for(auto item: route2stops)
    {
      cout << "Bus " << item.first << ": ";
      dump(item.second);
    }
}

int main()
{

  int ops;
  cin >> ops;
  for(int i = 0; i < ops; ++i)
  {
    string cmd;
    cin >> cmd;
    if(cmd == "ALL_BUSES")
    {
      all_buses();
      continue;
    }
    string arg1;
    cin >> arg1;
    if(cmd == "BUSES_FOR_STOP")
    {
      busses_for_stop(arg1);
      continue;
    }
    if(cmd == "STOPS_FOR_BUS")
    {
      stops_for_bus(arg1);
      continue;
    }
    if(cmd != "NEW_BUS")
      continue;
    // arg1 is route name
    int iStops = 0;
    cin >> iStops;
    for(int i = 0; i < iStops; i++)
    {
      string stop;
      cin >> stop;
      add_route_stop(arg1, stop);
    }
  }
  return 0;
}
