#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Напишите шаблонную функцию MergeSort, принимающую два итератора шаблонного типа RandomIt и 
 * сортирующую заданный ими диапазон с помощью сортировки слиянием. Гарантируется, что:
 * - итераторы типа RandomIt аналогичны по функциональности итераторам вектора и строки, 
 * то есть их можно сравнивать с помощью операторов <, <=, > и >=, 
 * а также вычитать и складывать с числами;
 * - сортируемые объекты можно сравнивать с помощью оператора <.
*/
template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
  //Если диапазон содержит меньше 2 элементов, выйти из функции.
  if(range_end - range_begin < 2)
    return;
  // Создать вектор, содержащий все элементы текущего диапазона.
  vector<typename RandomIt::value_type> elements(range_begin, range_end);

  // Разбить вектор на 3 равные части.
  auto d = distance(elements.begin(), elements.end()) / 3;
  RandomIt mid1 = elements.begin();
  advance(mid1, d);
  RandomIt mid2 = mid1;
  advance(mid2, d);

  // Вызвать функцию MergeSort от каждой части вектора.
  MergeSort(elements.begin(), mid1);
  MergeSort(mid1, mid2);
  MergeSort(mid2, elements.end());
  // Слить первые две трети вектора с помощью алгоритма merge, 
  //   сохранив результат во временный вектор с помощью back_inserter.
  vector<typename RandomIt::value_type> tmp;
  merge(elements.begin(), mid1, mid1, mid2, back_inserter(tmp));

  //  Слить временный вектор из предыдущего пункта с последней третью вектора из п. 2, 
  //   записав полученный отсортированный диапазон вместо исходного.
  merge(tmp.begin(), tmp.end(), mid2, elements.end(), range_begin);
}

/** 

Часть 2. Реализация с разбиением на 3 части

Реализуйте сортировку слиянием, разбивая диапазон на 3 равные части, а не на 2. 
Гарантируется, что длина исходного диапазона является степенью 3.

Соответственно, пункты 3–5 алгоритма нужно заменить следующими:

    Разбить вектор на 3 равные части.
    Вызвать функцию MergeSort от каждой части вектора.
    Слить первые две трети вектора с помощью алгоритма merge, 
     сохранив результат во временный вектор с помощью back_inserter.
    Слить временный вектор из предыдущего пункта с последней третью вектора из п. 2, 
     записав полученный отсортированный диапазон вместо исходного.


*/


int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}


/*
Вывод
0 1 4 4 4 5 6 6 7
*/
