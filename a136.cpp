#include <iostream>
#include <string>
#include <vector>
#include <algorithm> 
#include <ctype.h>

using namespace std;

/**
Реализуйте класс ReversibleString, хранящий строку и поддерживающий методы Reverse для переворота строки и ToString для получения строки. 
 * 
 */

class ReversibleString 
{
public:
  ReversibleString(const char *s) : _str(s) {}
  ReversibleString(const string &s) : _str(s) {}
  ReversibleString() {}

  void Reverse()
  {
    reverse(_str.begin(), _str.end());
  }
  string ToString() const
  {
    return _str;
  }

private:
  string _str;
};
/*
int main() 
{
  ReversibleString s("live");
  s.Reverse();
  cout << s.ToString() << endl;
  
  s.Reverse();
  const ReversibleString& s_ref = s;
  string tmp = s_ref.ToString();
  cout << tmp << endl;
  
  ReversibleString empty;
  cout << '"' << empty.ToString() << '"' << endl;

  string a;
  ReversibleString rs = a;
  
  return 0;
}
*/
/*
evil
live
""
*/