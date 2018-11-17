#include <iostream>
#include <vector>

using namespace std;

/**
 * Решите задачу «Средняя температура» в других ограничениях на входные данные.

Даны значения температуры, наблюдавшиеся в течение N подряд идущих дней. 
Найдите номера дней (в нумерации с нуля) со значением температуры выше среднего арифметического за все N дней.

Гарантируется, что среднее арифметическое значений температуры является целым числом.

Формат ввода
Вводится число N, затем N целых чисел — значения температуры в 0-й, 1-й, ... (N−1)-й день. 
Гарантируется, что N не превышает миллиона (10^6), а значения температуры, измеряющиеся в миллионных 
долях градусов по Цельсию, лежат в диапазоне от −10^8 до 10^8. Проверять соблюдение этих ограничений не нужно: 
вы можете ориентироваться на них при выборе наиболее подходящих типов для переменных.

Формат вывода
Первое число K — количество дней, значение температуры в которых выше среднего арифметического. Затем K целых чисел — номера этих дней.

Пример

Ввод
5
5000000 40000000 100000000 -2000000 700000000

Вывод
3
0 1 4

 * 
 */

int64_t calcAverage(const vector <int64_t> &temps)
{
  int64_t iTotal = 0;
  for(auto iTemp : temps)
    iTotal += iTemp;
  return iTotal/(int64_t)temps.size();
}

int main()
{
  vector <int64_t> temps;

  int iDays;
  cin >> iDays;
  for(int i = 0; i < iDays; ++i)
  {
    int64_t iTemp;
    cin >> iTemp;
    temps.push_back(iTemp);
  }

  int64_t iAverage = calcAverage(temps);

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
