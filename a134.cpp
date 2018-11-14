#include <iostream>
#include <string>
#include <vector>
#include <algorithm> 
#include <ctype.h>

using namespace std;

/**
Реализуйте класс для человека, поддерживающий историю изменений человеком своих фамилии и имени.
 * 
 */

string getName(const vector <pair<int, string>> &names, int year)
{
  string res("");
  for(int i = 0; i < names.size(); ++i)
    if(names[i].first <= year)
      res = names[i].second;
    else
      break;
  return res;
}

class Person 
{
public:
  void ChangeFirstName(int year, const string& name) 
  {
    pair<int,string> event = {year, name};
    _fn.push_back(event);
  }
  void ChangeLastName(int year, const string& name) 
  {
    pair<int,string> event = {year, name};
    _ln.push_back(event);
  }
  /** получить имя и фамилию по состоянию на конец года year */
  string GetFullName(int year) 
  {
    sort(_fn.begin(), _fn.end(), 
      [](const pair<int, string> &a, const pair<int, string> &b){ return a.first < b.first; });
    sort(_ln.begin(), _ln.end(), 
      [](const pair<int, string> &a, const pair<int, string> &b){ return a.first < b.first; });
    string fn = getName(_fn, year);
    string ln = getName(_ln, year);
    if(fn.size() == 0 && ln.size() == 0)
      return "Incognito";
    else if(fn.size() == 0)
      return ln + " with unknown first name";
    else if(ln.size() == 0)
      return fn + " with unknown last name";
    return fn + " " + ln;
  }
private:
  vector <pair<int, string>> _fn;
  vector <pair<int, string>> _ln;
};

int main() 
{
  Person person;
  
  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
    cout << person.GetFullName(year) << endl;
  }
  
  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }
  
  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }
  
  return 0;
}
/*
Incognito
Polina with unknown last name
Polina Sergeeva
Polina Sergeeva
Appolinaria Sergeeva
Polina Volkova
Appolinaria Volkova
*/
