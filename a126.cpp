#include <iostream>
#include <vector>

using namespace std;

/**
 * Реализуйте функцию void Reverse(vector<int>& v), которая переставляет элементы вектора в обратном порядке.
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

