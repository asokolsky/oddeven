#include <iostream>
#include <vector>

using namespace std;

/**
 * Реализуйте функцию vector<int> Reversed(const vector<int>& v), возвращающую копию вектора v, в которой числа переставлены в обратном порядке.
 */
void Reverse(vector<int>& v)
{
  int iHalfSize = v.size() / 2;  
  for(int i = 0; i < iHalfSize; ++i)
  {
    auto x = v[i];
    v[i] = v[v.size() - 1 - i];
    v[v.size() - 1 - i] = x;
  }
}

vector<int> Reversed(const vector<int>& v)
{
  vector<int> v1 = v;
  Reverse(v1);
  return v1;
}