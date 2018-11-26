#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Дано целое положительное число N, не превышающее 9. 
 * Выведите все перестановки чисел от 1 до N в обратном лексикографическом порядке (см. пример).

Подсказка
Библиотека <algorithm> содержит готовые функции, позволяющие решить эту задачу.

*/
void print(const char *msg, const vector<int> &v)
{
    cout << msg;
    for(int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;
}

void print(const vector<vector<int>> &vs)
{
    for(int i = 0; i < vs.size(); i++)
        print("", vs[i]); 
}

int main()
{
  int iLength = 0;
  cin >> iLength;
  // build a vector
  vector <int> v;
  for(int i = iLength; i >=1 ; i--)
    v.push_back(i);
  // v built

  // build all the possible permutations
  vector <vector<int>> vs;
  do {
    //print("permutation: ", v);
    vs.push_back(v);
  } while (next_permutation(v.rbegin(), v.rend()));

  sort(vs.rbegin(), vs.rend());
  print(vs);
  return 0;
}

/*
 * Ввод
 * 3
 * Вывод:
3 2 1
3 1 2
2 3 1
2 1 3
1 3 2
1 2 3


*/
