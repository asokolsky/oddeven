#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>


using namespace std;

/**
В первой строке файла input.txt записаны два числа N и M. 
Далее в файле находится таблица из N строк и M столбцов, 
представленная в формате CSV (comma-separated values). 
Такой формат часто используется для текстового представления таблиц с данными: 
в файле несколько строк, значения из разных ячеек внутри строки отделены друг от друга запятыми. 
Ваша задача — вывести данные на экран в виде таблицы, размер ячейки которой равен 10, соседние ячейки отделены друг от друга пробелом. 
После последней ячейки пробела быть не должно. 
Гарантируется, что в таблице будет ровно N строк и M столбцов, значение каждой из ячеек — целое число.
Пример ввода
2 3
1,2,3
4,5,6
Пример вывода
         1          2          3
         4          5          6

 * 
 */

int main() 
{
  ifstream input("input.txt");
  if(!input)
    return 1;
  int iLines = 0, iCols = 0;
  input >> iLines >> iCols;

  cout << fixed << setprecision(3);
  for(int i = 0; (i < iLines) && input; i++)
  {
    //vector <int> ints;
    for(int i = 0; (i < iCols) && input; i++)
    {
      int v;
      input >> v;
      //ints.push_back(v);
      cout << setw(10) << v;
      if(i < (iCols - 1))
      {
        input.ignore(1);
        cout << " ";
      }
      else
      {
        cout << endl;
      }
    }
  }
  //cout << endl;
  //cout << iLines << " lines read" << endl;
  return 0;
}
