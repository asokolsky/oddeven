#include <iostream>
#include <map>
#include <string>
#include <set>


using namespace std;

/**
Дан набор строк. 
Найдите количество уникальных строк в этом наборе.

Формат ввода

Сначала вводится количество строк N, затем — сами N строк, разделённые пробелом. 
Все строки состоят лишь из латинских букв, цифр и символов подчёркивания.

Формат вывода
Выведите единственное целое число — количество уникальных строк в данном наборе.
 */

int main()
{
  int ops;
  cin >> ops;
  set <string> uniqueStrings;
  for(int i = 0; i < ops; ++i)
  {
    string str;
    cin >> str;
    uniqueStrings.insert(str);
  }
  cout << uniqueStrings.size() << endl;

  return 0;
}
