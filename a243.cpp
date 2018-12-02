#include <algorithm>
#include <iostream>
//#include <set>
#include <vector>

using namespace std;

/**
 * Напишите функцию SplitIntoWords, разбивающую строку на слова по пробелам.
 * Гарантируется, что:

    строка непуста;
    строка состоит лишь из латинских букв и пробелов;
    первый и последний символы строки не являются пробелами;
    строка не содержит двух пробелов подряд.

Подсказка

Рекомендуется следующий способ решения задачи:

    искать очередной пробел с помощью алгоритма find;
    создавать очередное слово с помощью конструктора строки по двум итераторам.
 */

vector<string> SplitIntoWords(const string& s)
{
  vector<string> res;
  for(auto b=s.begin(); b < s.end();)
  {
    auto e = find(b, s.end(), ' ');
    string elt(b, e);
    res.push_back(elt);
    if(e == s.end())
      break;
    b = ++e;
  }
  return res;
}

int main() {
  string s = "C Cpp Java Python";

  vector<string> words = SplitIntoWords(s);
  cout << words.size() << " ";
  for (auto it = begin(words); it != end(words); ++it) {
    if (it != begin(words)) {
      cout << "/";
    }
    cout << *it;
  }
  cout << endl;
  
  return 0;
}

/*
4 С/Cpp/Java/Python
*/
