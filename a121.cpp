#include <iostream>
#include <vector>
using namespace std;

/**
 * Напишите функцию, которая
 * называется Factorial
 * возвращает int
 * принимает int и возвращает факториал своего аргумента. 
 * Гарантируется, что аргумент функции по модулю не превышает 10. Для отрицательных аргументов функция должна возвращать 1.
 */
int Factorial(int i)
{
  if(i <= 0)
    return 1;
  return i * Factorial(i - 1);
}

int main()
{
  int n;
  cin >> n;
  cout << Factorial(n) << endl;
  return 0;
}
