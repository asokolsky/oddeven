#include <iostream>
#include <string>
#include <vector>
#include <algorithm> 
#include <ctype.h>

using namespace std;

/**
Условие

В стандартном потоке дана одна строка, состоящая из числа N и следующих за ним N строк S. Между собой число и строки разделены пробелом.

Отсортируйте строки S в лексикографическом порядке по возрастанию, игнорируя регистр букв, и выведите их в стандартный поток вывода.
Ограничения

    0 <= N <= 1000
    1 <= |S| <= 15
    Каждая строка S[i] может состоять из следующих символов: [0-9,a-z,A-Z]

Примеры
stdin	stdout
2 q A	A q
3 a C b	a b C
Подсказка

Обратите внимание на функцию tolower.
 * 
 */

string toLower(string str)
{
  /*
  transform(str.begin(), str.end(), str.begin(), tolower);
  */
  for(auto &ch: str)
    ch = tolower(ch);
  return str;
}

int main()
{
  int n;
  cin >> n;
  vector<string> v(n);
  for (auto& x : v)
    cin >> x;

  // сортируем
  sort(begin(v), end(v), 
    //[](const string &l, const string &r) { return toLower(l) < toLower(r); });
       [](const string& l, const string& r) {
         // сравниваем лексикографически...
         return lexicographical_compare(
             // ... все символы строки l ...
             begin(l), end(l),
             // ... со всеми символами строки r ...
             begin(r), end(r),
             // ..., используя в качестве компаратора сравнение отдельных символов без учёта регистра
             [](char cl, char cr) { return tolower(cl) < tolower(cr); }
         );
       }
  );

  // выводим отсорированный вектор
  for (auto x : v) {
    cout << x << " ";
  }

  return 0;
}
