#include <iostream>
#include <string>
using namespace std;

/**
 * find 2nd occurance
 * Дана строка. 
 * Найдите в этой строке второе вхождение буквы f и выведите индекс этого вхождения. 
 * Если буква f в данной строке встречается только один раз, выведите число -1, 
 * а если не встречается ни разу, выведите число -2. 
 * Индексы нумеруются с нуля.
 */
int main()
{
  string a;
  cin >> a;
  int iOccurancesOff = 0;
  int iSecondfIndex = -1;
  for(int i = 0; i < a.size(); i++)
  {
    if(a[i] == 'f')
    {
      ++iOccurancesOff;
      if(iOccurancesOff == 2) {
        iSecondfIndex = i;
        break;
      }
    }
  }
  if(iOccurancesOff == 0)
    cout << -2 << endl;
  else if (iOccurancesOff == 1)
    cout << -1 << endl;
  else
    cout << iSecondfIndex << endl;
  return 0;
}
