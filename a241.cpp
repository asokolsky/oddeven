#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Напишите функцию PrintVectorPart, принимающую вектор целых чисел numbers, 
 * выполняющую поиск первого отрицательного числа в нём 
 * и выводящую в стандартный вывод все числа, расположенные левее найденного, в обратном порядке. 
 * Если вектор не содержит отрицательных чисел, выведите все числа в обратном порядке.
 */


void PrintVectorPart(const vector<int>& numbers)
{
    auto negative_it = find_if(
        numbers.begin(), numbers.end(),
        [](int number) {
        return number < 0;
        }
    );

    for (auto it = negative_it; it != numbers.begin(); ) {
        cout << *(--it) << " ";
    }
}

int main() {
  PrintVectorPart({6, 1, 8, -5, 4});
  PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
  PrintVectorPart({6, 1, 8, 5, 4});
  return 0;
}

/*
8 1 6

4 5 8 1 6
*/
