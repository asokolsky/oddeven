#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <numeric>


using namespace std;

int main() 
{
set<string> s = {"a", "b", "c", "b", "e" };
auto range = s.equal_range("b");


  next(range.first) == prev(range.second);

  range.first == prev(range.second);

  prev(range.first) == range.second;

  range.first == next(range.second);

  next(range.first) == range.second;

  range.first == range.second;

  prev(range.first) == next(range.second);

  return 0;
}
