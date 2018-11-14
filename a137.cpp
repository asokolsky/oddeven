#include <iostream>
#include <string>
#include <vector>
#include <algorithm> 
#include <ctype.h>

using namespace std;

/**
Дополните класс Person из задачи «Имена и фамилии — 2» конструктором, 
позволяющим задать имя и фамилию человека при рождении, а также сам год рождения. 
Класс не должен иметь конструктора по умолчанию.

При получении на вход года, который меньше года рождения:

    методы GetFullName и GetFullNameWithHistory должны отдавать "No person";
    методы ChangeFirstName и ChangeLastName должны игнорировать запрос.

Кроме того, необходимо объявить константными все методы, которые по сути ими являются.
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
  Person(const string& fn, const string& ln, int year) : _yob(year)
  {
    pair<int,string> event = {year, fn};
    _fn.push_back(event);
    event.second = ln;
    _ln.push_back(event);
  }
  void ChangeFirstName(int year, const string& name) 
  {
    if(year < _yob)
      return;
    pair<int,string> event = {year, name};
    _fn.push_back(event);
    sort(_fn.begin(), _fn.end(), 
      [](const pair<int, string> &a, const pair<int, string> &b){ return a.first < b.first; });
  }
  void ChangeLastName(int year, const string& name) 
  {
    if(year < _yob)
      return;
    pair<int,string> event = {year, name};
    _ln.push_back(event);
    sort(_ln.begin(), _ln.end(), 
      [](const pair<int, string> &a, const pair<int, string> &b){ return a.first < b.first; });
  }
  /** получить имя и фамилию по состоянию на конец года year */
  string GetFullName(int year) const
  {
    if(year < _yob)
      return "No person";
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
  string GetFullNameWithHistory(int year) const
  {
    if(year < _yob)
      return "No person";
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
  int _yob;
};

int main() 
{
  Person person("Polina", "Sergeeva", 1960);
  for (int year : {1959, 1960}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeFirstName(1965, "Appolinaria");
  person.ChangeLastName(1967, "Ivanova");
  for (int year : {1965, 1967}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  return 0;
}

/*
No person
Polina Sergeeva
Appolinaria (Polina) Sergeeva
Appolinaria (Polina) Ivanova (Sergeeva)
*/
