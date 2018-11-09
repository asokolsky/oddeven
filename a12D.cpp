#include <iostream>
#include <map>
#include <string>


using namespace std;

/**
 * Реализуйте справочник столиц стран.
 * На вход программе поступают следующие запросы:
 * 
 * CHANGE_CAPITAL country new_capital — изменение столицы страны country на new_capital, 
 * либо добавление такой страны с такой столицей, если раньше её не было.
 * 
 * RENAME old_country_name new_country_name — переименование страны из old_country_name в new_country_name.
 * 
 * ABOUT country — вывод столицы страны country.
 * 
 * DUMP — вывод столиц всех стран.
 * 
 * Формат ввода
 * В первой строке содержится количество запросов Q, в следующих Q строках — описания запросов. 
 * Все названия стран и столиц состоят лишь из латинских букв, цифр и символов подчёркивания.
 * 
 */

void dump(map <string, string> &world)
{
  if(world.size() == 0)
    cout <<  "There are no countries in the world" << endl;
  else
  {
    for(auto item : world)
      cout << item.first << "/" << item.second << " ";
    cout << endl;
  }
}
void dump(map <string, string> &world, const string &country)
{
  if(world.count(country) == 0)
    cout <<  "Country " << country << " doesn't exist" << endl;
  else
    cout <<  "Country " << country << " has capital " << world[country] << endl;
}
void changeCapital(map <string, string> &world, const string &country, const string &capital)
{
  if(world.count(country) == 0)
  {
    cout << "Introduce new country " << country << " with capital " << capital << endl;
    world[country] = capital;
  }
  else if(capital == world[country])
  {
    cout << "Country " << country << " hasn't changed its capital" << endl;
  }
  else
  {
    cout << "Country " << country << " has changed its capital from " << world[country] << "  to " << capital << endl;
    world[country] = capital;
  }

}
void renameCountry(map <string, string> &world, const string &country, const string &newCountry)
{
  if((country == newCountry) || (world.count(country) == 0) || (world.count(newCountry) != 0))
    cout <<  "Incorrect rename, skip" << endl;
  else
  {
    string capital = world[country];
    cout <<  "Country " << country << " with capital " << capital << " has been renamed to " << newCountry << endl;
    world.erase(country);
    world[newCountry] = capital;
  }
}

int main()
{
  map <string, string> world;

  int ops;
  cin >> ops;
  for(int i = 0; i < ops; ++i)
  {
    string cmd;
    cin >> cmd;
    if(cmd == "DUMP")
    {
      dump(world);
      continue;
    }
    string arg1;
    cin >> arg1;
    if(cmd == "ABOUT")
    {
      dump(world, arg1);
      continue;
    }
    string arg2;
    cin >> arg2;
    if(cmd == "CHANGE_CAPITAL")
      changeCapital(world, arg1, arg2);
    else if(cmd == "RENAME")
      renameCountry(world, arg1, arg2);
  }
  return 0;
}
