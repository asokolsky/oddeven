#include <iostream>
#include <string>
#include <vector>
#include <algorithm> 
#include <ctype.h>

using namespace std;

/**
Дополните класс из предыдущей задачи «Имена и фамилии — 1» методом GetFullNameWithHistory:
 * 
 */
string getName(const vector<string> &names)
{
  string res;
  if(!names.empty())
  {
    res = names[0];
    if(names.size() > 1)
    {
      res += " (";
      for(int i = 1; i < names.size(); ++i)
      {
        res += names[i];
        if(i < (names.size() - 1))
          res += ", ";
      } 
      res += ")";
    }
  }
  return res;
}

vector<string> getName(const vector <pair<int, string>> &names, int year)
{
  vector<string> res;
  string lastused; // to ignore trivial changes
  for(int i = 0; i < names.size(); ++i)
    if(names[i].first <= year)
    {
      if(lastused != names[i].second)
        res.push_back(names[i].second);
      lastused = names[i].second;
    }
  reverse(res.begin(), res.end()); 
  return res;
}

class Person 
{
public:
  void ChangeFirstName(int year, const string& name) 
  {
    pair<int,string> event = {year, name};
    _fn.push_back(event);
    sort(_fn.begin(), _fn.end(), 
      [](const pair<int, string> &a, const pair<int, string> &b){ return a.first < b.first; });
  }
  void ChangeLastName(int year, const string& name) 
  {
    pair<int,string> event = {year, name};
    _ln.push_back(event);
    sort(_ln.begin(), _ln.end(), 
      [](const pair<int, string> &a, const pair<int, string> &b){ return a.first < b.first; });
  }
  /** получить имя и фамилию по состоянию на конец года year */
  string GetFullName(int year) 
  {
    vector<string> fn = getName(_fn, year);
    vector<string> ln = getName(_ln, year);
    if(fn.empty() && ln.empty())
      return "Incognito";
    else if(fn.empty())
      return ln[0] + " with unknown first name";
    else if(ln.empty())
      return fn[0] + " with unknown last name";
    return fn[0] + " " + ln[0];
  }
  string GetFullNameWithHistory(int year) 
  {
    vector<string> fn = getName(_fn, year);
    vector<string> ln = getName(_ln, year);
    if(fn.empty() && ln.empty())
      return "Incognito";
    else if(fn.empty())
      return getName(ln) + " with unknown first name";
    else if(ln.empty())
      return getName(fn) + " with unknown last name";
    return getName(fn) + " " + getName(ln);
  }

private:
  vector <pair<int, string>> _fn;
  vector <pair<int, string>> _ln;
};

#if 0
int main() 
{
  Person person;
/*
  person.ChangeFirstName(1900, "Eugene");
  person.ChangeLastName(1900, "Sokolov");
  person.ChangeLastName(1910, "Sokolov");
  person.ChangeFirstName(1920, "Evgeny");
  person.ChangeLastName(1930, "Sokolov");
  cout << person.GetFullNameWithHistory(1940) << endl;
*/

  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeFirstName(1990, "Polina");
  person.ChangeLastName(1990, "Volkova-Sergeeva");
  cout << person.GetFullNameWithHistory(1990) << endl;
  
  person.ChangeFirstName(1966, "Pauline");
  cout << person.GetFullNameWithHistory(1966) << endl;
  
  person.ChangeLastName(1960, "Sergeeva");
  for (int year : {1960, 1967}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeLastName(1961, "Ivanova");
  cout << person.GetFullNameWithHistory(1967) << endl;

  return 0;
}
#endif

/*
Evgeny (Eugene) Sokolov
*/
/*
Incognito
Polina with unknown last name
Polina Sergeeva
Polina Sergeeva
Appolinaria (Polina) Sergeeva
Polina Volkova (Sergeeva)
Appolinaria (Polina) Volkova (Sergeeva)
Polina (Appolinaria, Polina) Volkova-Sergeeva (Volkova, Sergeeva)
Pauline (Polina) with unknown last name
Sergeeva with unknown first name
Pauline (Polina) Sergeeva
Pauline (Polina) Sergeeva (Ivanova, Sergeeva)
*/
