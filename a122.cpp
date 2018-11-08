#include <iostream>
#include <string>
using namespace std;

/**
 * Напишите функцию, которая
    называется IsPalindrom
    возвращает bool
    принимает параметр типа string и возвращает, является ли переданная строка палиндромом
  Палиндром - это слово или фраза, которые одинаково читаются слева направо и справа налево. 
  Пустая строка является палиндромом.
*/

bool IsPalindrom(string s)
{
  if(s.size() == 0)
    return true;
  int iHalfLength = s.size() / 2;
  for(int i = 0; i < iHalfLength ; ++i)
    if(s[i] != s[s.size() - 1 - i])
      return false;
  return true;
}

int main()
{
  string s;
  cin >> s;
  cout << (IsPalindrom(s) ? "true" : "false") << endl;
  return 0;
}
