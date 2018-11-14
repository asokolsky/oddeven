#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

/**
В файле input.txt записаны вещественные числа, по одному на строчку. 
На стандартный вывод напечатайте эти числа в том же порядке, по одному на строке, но сделайте так, 
чтобы у каждого из них было ровно три знака после десятичной точки 
(округление производится по стандартным правилам, т.е. 0.1234 округляется до 0.123, а 0.1235 до 0.124).

Пример ввода 1
5
0.34567
10.4

Пример вывода 1
5.000
0.346
10.400

Пример ввода 2
3.33353
3.333
3.3

Пример вывода 2
3.334
3.333
3.300

 * 
 */

int main() 
{
  ifstream input("input.txt");
  if(!input)
    return 1;
  cout << fixed << setprecision(3);
  while(input)
  {
    double num;
    input >> num;
    if(!input)
      break;
    cout << num << endl;
  }
  //cout << endl;
  //cout << iLines << " lines read" << endl;
  return 0;
}
