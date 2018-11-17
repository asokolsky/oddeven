#include <iostream>
#include <vector>
#include <map>

using namespace std;

/**
 * Имеется база регионов, представленная вектором структур Region: 
 */
/*
// Lang — идентификатор языка:
enum class Lang {DE, FR, IT};

struct Region 
{
  string std_name;
  string parent_std_name;
  map<Lang, string> names;
  int64_t population;
};
*/
/**
Напишите функцию FindMaxRepetitionCount, принимающую базу регионов и определяющую, какое максимальное количество повторов она содержит. 
Две записи (объекты типа Region) считаются различными, если они отличаются хотя бы одним полем. 
int FindMaxRepetitionCount(const vector<Region>& regions);

Если все записи уникальны, считайте максимальное количество повторов равным 1. 
Если записи отсутствуют, верните 0. 
Гарантируется, что типа int достаточно для хранения ответа.

Пояснение

В этой задаче вам надо прислать на проверку файл с реализацией функции FindMaxRepetitionCount, 
а также дополнительных функций, если это необходимо. Этот файл не должен содержать типы Lang и Region. 
В противном случае вы получите ошибку компиляции.
 * 
 */

/*inline bool operator<(const Region &lhs, const Region &rhs) 
{
  if(lhs.std_name != rhs.std_name)
    return lhs.std_name < rhs.std_name;
  if(lhs.parent_std_name != rhs.parent_std_name)
    return lhs.parent_std_name < rhs.parent_std_name;
  if(lhs.population != rhs.population)
    return lhs.population < rhs.population;
  return lhs.names < rhs.names;
}*/

bool operator<(const Region& lhs, const Region& rhs) {
  return tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population) <
      tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}


int FindMaxRepetitionCount(vector<Region> &rs)
{
  // count all the given regions
  map<Region, int> rMap;
  for(const Region &r: rs)
  {
    int iRegionCounter = (rMap.count(r) != 0) ? rMap[r] : 0;
    rMap[r] = 1 + iRegionCounter;
  }
  // fin the max region
  int iMax = 0;
  for(auto &keyval: rMap)
    if(keyval.second > iMax)
      iMax = keyval.second;
  return iMax;
}
/*
vector<Region> rs1 = {
      {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Russia",
          "Eurasia",
          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Russia",
          "Eurasia",
          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
          89
      },
  };

vector<Region> rs2 = {
      {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Russia",
          "Eurasia",
          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Moscow",
          "Toulouse",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          31
      },
  };


int main() 
{
  cout << FindMaxRepetitionCount(rs1) << endl;
  cout << FindMaxRepetitionCount(rs2) << endl;
  return 0;
}
*/
/** 
 * Вывод
3
1
*/