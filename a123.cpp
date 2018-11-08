#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * Напишите функцию, которая
    называется PalindromFilter
    возвращает vector<string>
    принимает vector<string> words и int minLength и 
    возвращает все строки из вектора words, 
    которые являются палиндромами и имеют длину не меньше minLength
   Входной вектор содержит не более 100 строк, длина каждой строки не больше 100 символов.
*/
bool IsPalindrom(string s)
{
  if(s.size() == 0)
    return true;
  int iHalfLength = s.size() / 2;
  for(int i = 0; i < iHalfLength ; ++i)
    if(s[i] != s[s.size() - 1 - i])
      return false;
  return true;
}

vector<string> PalindromFilter(vector<string> words, int minLength)
{
  vector<string> res;
  for(auto word: words)
    if(word.size() < minLength)
      continue;
    else if(IsPalindrom(word))
      res.push_back(word);
  return res;
}

int main()
{
  vector<string> words;
  int minLength = 0;
  for(;;)
  {
    string word;
    cin >> word;
    //cout << word << endl;
    if(word[word.size()-1] == ',')
      words.push_back(word.substr(0, word.size()-1));
    else if(isdigit(word[0]))
    {
      minLength = stoi(word);
      break;
    }
    else
      words.push_back(word);

  }
  vector<string> pals = PalindromFilter(words, minLength);
  for(int i = 0; i < pals.size(); )
  {
    cout << pals[i];
    i++;
    if(i < pals.size())
      cout << ", ";
  }
  cout << endl;
  return 0;
}
