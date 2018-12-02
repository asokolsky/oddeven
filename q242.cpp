#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <numeric>


using namespace std;

vector<int> vec;
auto vector_begin = begin(vec);
auto vector_end = end(vec);

string str;
auto string_begin = begin(str);
auto string_end = end(str);

set<int> s;
auto set_begin = begin(s);
auto set_end = end(s);

int main() 
{
  //auto res5 = is_permutation(set_begin, set_end, back_inserter(vec));
  auto res7 = is_permutation(set_begin, set_end, vector_begin);
  //partial_sum(vector_begin, vector_end, set_begin);
  auto res6 = next_permutation(string_begin, string_end);
  auto res9 = accumulate(vector_begin, vector_end, 0); 
  //auto res10 = next_permutation(set_begin, set_end);
  partial_sum(set_begin, set_end, back_inserter(vec));
  auto res1 = accumulate(set_begin, set_end, 0);
  //auto res8 = is_heap(set_begin, set_end);
  partial_sum(set_begin, set_end, vector_begin);
  auto res55 = is_permutation(vector_begin, vector_end, vector_begin);
  auto res0 = is_heap(string_begin, string_end);

  return 0;
}
