#include <iostream>
#include <vector>
using namespace std;

/**
 * На вход дано целое положительное число N. Выведите его в двоичной системе счисления без ведущих нулей.
 * Подсказка: 
 *   - число N можно считывать в переменную типа int 
 *   - в этой задаче вам может пригодиться контейнер vector; напоминаем, что добавление значения x в конец вектора v делается так: v.push_back(x);
 */
int main()
{
  int n;
  cin >> n;
  vector<char> v;
  for(;n > 0; n = n / 2)
    v.push_back((n % 2 == 0) ? '0' : '1');
  for(int i = v.size()-1; i >=0 ; --i)
    cout << v[i];
  cout << endl;
  return 0;
}
