#include <iostream>
#include <map>
#include <string>
#include <set>


using namespace std;

/**
Два слова называются синонимами друг друга, если они имеют похожие значения. 
Реализуйте следующие операции над словарём синонимов:

    ADD word1 word2 — добавить в словарь пару синонимов (word1, word2).
    COUNT word — узнать количество синонимов слова word.
    CHECK word1 word2 — проверить, являются ли слова word1 и word2 синонимами. 
    Слова word1 и word2 считаются синонимами, если среди запросов ADD был хотя бы один запрос ADD word1 word2 или ADD word2 word1.

Формат ввода
Сначала вводится количество запросов Q, затем Q строк с описаниями запросов. 
Гарантируется, что в каждом запросе CHECK и ADD слова word1 и word2 различны. 
Все слова состоят лишь из латинских букв, цифр и символов подчёркивания.

Формат вывода
Для каждого запроса в соответствующей строке выведите ответ на него:
    В ответ на запрос COUNT word выведите единственное целое число — количество синонимов слова word.
    В ответ на запрос CHECK word1 word2 выведите строку YES, если word1 и word2 являются синонимами, 
    и NO в противном случае.
 */

map <string /* word */, set <string> /* synonyms */> synonyms;


int main()
{
  int ops;
  cin >> ops;
  for(int i = 0; i < ops; ++i)
  {
    string cmd, w1;
    cin >> cmd >> w1;
    if(cmd == "COUNT")
    {
      if(synonyms.count(w1) == 0)
        cout << "0" << endl;
      else
        cout << synonyms[w1].size() << endl;
      continue;
    }
    string w2;
    cin >> w2;
    if(cmd == "ADD")
    {
      synonyms[w1].insert(w2);
      synonyms[w2].insert(w1);
      continue;
    }
    if(cmd == "CHECK")
    {
      if(synonyms.count(w1) == 0)
        cout << "NO" << endl;
      else
        cout << ((synonyms[w1].count(w2) ==  0) ? "NO" : "YES") << endl;
      continue;
    }
    
  }
  return 0;
}

