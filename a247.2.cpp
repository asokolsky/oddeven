#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

/**
 * Часть 2. Группировка по префиксу

Напишите более универсальный вариант функции FindStartsWith, 
принимающий в качестве префикса произвольную строку, состоящую из строчных латинских букв.

*/

template <typename RandomIt> 
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, const string& prefix)
{
  pair<RandomIt, RandomIt> res;
  string strPrefix(prefix);
  res.first = lower_bound(range_begin, range_end, strPrefix);
  if(res.first != range_end)
  {
    // found it!
    strPrefix[strPrefix.size()-1]++;
    res.second = lower_bound(res.first, range_end, strPrefix);
  }
  else
  {
    // nothing found!
    res.second = res.first;
  }
  return res;
}

int main() {

  const vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};
  
  const auto mo_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
  for (auto it = mo_result.first; it != mo_result.second; ++it) {
    cout << *it << " ";
  }
  cout << endl;
  
  const auto mt_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
  cout << (mt_result.first - begin(sorted_strings)) << " " <<
      (mt_result.second - begin(sorted_strings)) << endl;
  
  const auto na_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
  cout << (na_result.first - begin(sorted_strings)) << " " <<
      (na_result.second - begin(sorted_strings)) << endl;
  
  return 0;
}


/*
moscow motovilikha
2 2
3 3
*/
