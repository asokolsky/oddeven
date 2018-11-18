#include <iostream>
#include <vector>
#include <map>

using namespace std;

/**
 * Реализуйте шаблонную функцию Sqr, которая работает не только для чисел, но и для контейнеров. 
 * Функция должна возвращать копию исходного контейнера, модифицировав его следующим образом:

    для vector элементы нужно возвести в квадрат;
    для map в квадрат нужно возвести только значения, но не ключи;
    для pair в квадрат нужно возвести каждый элемент пары.

   Функция должна корректно работать не только для контейнеров, состоящих из чисел, 
   но и для составных объектов, например, векторов словарей пар чисел.

  Для успешной сдачи решения необходимо сделать предварительное объявление шаблонных функций перед всеми шаблонными функциями.

 */

// Предварительное объявление шаблонных функций
template<typename T> T Sqr(const T& x);
template <typename K, typename V> map<K, V> Sqr(const map<K, V> &x);
template <typename T1, typename T2> pair<T1, T2> Sqr(const pair<T1, T2> &x);
template <typename E> vector<E> Sqr(const vector<E> &x);

// Объявляем шаблонные функции
template <typename T>
T Sqr(const T& x) { 
    return x * x; 
}
template <typename T1, typename T2>
pair<T1, T2> Sqr(const pair<T1, T2>&x) { 
    return make_pair(Sqr(x.first), Sqr(x.second)); 
}
template <typename E> 
vector<E> Sqr(const vector<E>& x)
{
    vector<E> res = x;
    for(auto &e : res)
        e = Sqr(e);
    return res;
}
template <typename K, typename V>
map<K, V> Sqr(const map<K, V>& x)
{
    map<K, V> res = x;
    for(auto &e : res)
        e.second = Sqr(e.second);
    return res;
}
/*
int main()
{
    // Пример вызова функции
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v))
        cout << ' ' << x;
    cout << endl;

    map<int, pair<int, int>> map_of_pairs = {
        {4, {2, 2}},
        {7, {4, 3}}
    };
    cout << "map of pairs:" << endl;
    for (const auto& x : Sqr(map_of_pairs))
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
}
*/
/*
vector: 1 4 9
map of pairs:
4 4 4
7 16 9
*/
