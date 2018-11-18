#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <stdexcept>

using namespace std;

/**
 * Реализуйте шаблонную функцию GetRefStrict, которая на вход принимает: 
 * map и значение ключа k. Если элемент по ключу k в коллекции отсутствует, 
 * то функция должна бросить исключение runtime_error, 
 * иначе вернуть ссылку на элемент в коллекции.
 */

// Предварительное объявление шаблонных функций
template<typename K, typename V> V& GetRefStrict(map<K, V>&, const K);

template<typename K, typename V> 
V& GetRefStrict(map<K, V>&m , const K k)
{
    if(m.count(k) == 0)
        throw runtime_error("GetRefStrict: key does not exist");
    return m[k];
}
/*
int main()
{
map<int, string> m = {{0, "value"}};
string& item = GetRefStrict(m, 0);
item = "newvalue";
cout << m[0] << endl; // выведет newvalue
}
*/