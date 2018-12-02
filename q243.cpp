#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <numeric>


using namespace std;

void print(const char *msg, const vector<int> &v)
{
    cout << msg;
    for(int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;
}

int main() 
{
  vector <int> v = {1, 2, 3, 1, 5, 2, 1};
  auto it1 = is_sorted_until(begin(v), end(v));
  auto it2 = is_sorted_until(rbegin(v), rend(v));
  // Максимальный суффикс (участок в конце) вектора, отсортированный по убыванию.

  return 0;
}
