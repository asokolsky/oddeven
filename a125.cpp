#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * Напишите функцию MoveStrings, которая принимает два вектора строк, source и destination, 
 * и дописывает все строки из первого вектора в конец второго. 
 * После выполнения функции вектор source должен оказаться пустым. Чтобы очистить содержимое вектора, надо вызвать у него метод clear
*/
void MoveStrings(vector <string> &source, vector <string> &destination)
{
  for(auto s: source)
    destination.push_back(s);
  source.clear();
}

