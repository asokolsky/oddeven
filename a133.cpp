#include <iostream>
#include <string>
#include <vector>
#include <algorithm> 
#include <ctype.h>

using namespace std;

/**
Реализуйте класс, поддерживающий набор строк в отсортированном порядке. Класс должен содержать два публичных метода: 

 * 
 */

class SortedStrings 
{
public:
  void AddString(const string& s) 
  {
    _strings.push_back(s);
  }
  vector<string> GetSortedStrings() 
  {
    vector<string> res = _strings;
    sort(res.begin(), res.end());
    return res;
  }
private:
  vector <string> _strings;
};
/*
void PrintSortedStrings(SortedStrings& strings) 
{
  for (const string& s : strings.GetSortedStrings()) 
  {
    cout << s << " ";
  }
  cout << endl;
}

int main() 
{
  SortedStrings strings;
  
  strings.AddString("first");
  strings.AddString("third");
  strings.AddString("second");
  PrintSortedStrings(strings);
  
  strings.AddString("second");
  PrintSortedStrings(strings);
  
  return 0;
}
*/