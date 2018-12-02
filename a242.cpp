#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

/**
 * Напишите шаблонную функцию FindGreaterElements, 
 * принимающую множество elements объектов типа T 
 * и ещё один объект border типа T 
 * и возвращающую вектор из всех элементов множества, бо́льших border, в возрастающем порядке.
 */

template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border)
{
    /*
    vector<T> res;
    for(auto elt: elements)
        if(elt > border)
            res.push_back(elt);
    sort(res.begin(), res.end());
    return res;
    */
  // Начнём итерироваться по множеству
  auto it = begin(elements);
  // Цель — найти первый элемент, больший border
  // Если итератор не достиг конца и указывает не туда, двигаем
  while (it != end(elements) && *it <= border) {
  	++it;
  }
  // Возвращаем вектор, созданный из элементов множества, начиная с it
  return {it, end(elements)};   
}

int main() {
  for (int x : FindGreaterElements(set<int>{1, 5, 7, 8}, 5)) {
    cout << x << " ";
  }
  cout << endl;
  
  string to_find = "Python";
  cout << FindGreaterElements(set<string>{"C", "C++"}, to_find).size() << endl;
  return 0;
}


/*
7 8
0
*/