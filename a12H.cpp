#include <iostream>
#include <map>
#include <string>
#include <set>


using namespace std;

/**
Напишите функцию BuildMapValuesSet, принимающую на вход словарь map<int, string> и возвращающую множество значений этого словаря:
 */

set <string> BuildMapValuesSet(const map<int, string>& m) 
{
  set <string> res;
  for(auto &elt: m)
    res.insert(elt.second);
  return res;
}
