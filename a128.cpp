#include <iostream>
#include <vector>

using namespace std;

/**
 * Даны значения температуры, наблюдавшиеся в течение N подряд идущих дней. 
 * Найдите номера дней (в нумерации с нуля) со значением температуры выше среднего арифметического за все N дней.
 * Гарантируется, что среднее арифметическое значений температуры является целым числом.
 * 
 * Формат ввода
 * Вводится число N, 
 * затем N неотрицательных целых чисел — значения температуры в 0-й, 1-й, ... (N−1)-й день.
 * 
 * Формат вывода
 * Первое число K — количество дней, значение температуры в которых выше среднего арифметического. 
 * Затем K целых чисел — номера этих дней.
 * 
 */

int calcAverage(const vector <int> &temps)
{
  int iTotal = 0;
  for(auto iTemp : temps)
    iTotal += iTemp;
  return iTotal/temps.size();
}

int main()
{
  vector <int> temps;

  int iDays;
  cin >> iDays;
  for(int i = 0; i < iDays; ++i)
  {
    int iTemp;
    cin >> iTemp;
    temps.push_back(iTemp);
  }

  int iAverage = calcAverage(temps);

  // indexes in temps of days with higher than average temperatures
  vector <int> highTemps;
  for(int i = 0; i < temps.size(); ++i)
    if(temps[i] > iAverage)
      highTemps.push_back(i);

  // output
  cout << highTemps.size() << endl;
  for(int i = 0; i < highTemps.size(); ++i)
    cout << highTemps[i] << " ";
  cout << endl;
  return 0;
}
