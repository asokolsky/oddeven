#include "database.h"

void Database::Add(const Date& date, const string& event)
{
    if(!event.empty())
        _m[date].insert(event);
}
/*bool Database::DeleteEvent(const Date& date, const string& event)
{
    if(_m.count(date) == 0)
        return false;
    set<string> &strs = _m[date];
    set<string>::iterator it = strs.find(event);
    if(it == strs.end())
        return false;
    strs.erase(it);
    return true;
}*/
/*int Database::DeleteDate(const Date& date)
{
    if(_m.count(date) == 0)
        return 0;
    int iRes = _m.at(date).size();
    _m.erase(date);
    return iRes;
}*/
/*void Database::Find(const Date& date) const
{
    auto it = _m.find(date);
    if(it != _m.end())
    {
        for(auto evt: it->second)
            cout << date << " " << evt << endl;
    }
}*/
void Database::Print(std::ostream& os) const
{
  for(auto &elt: _m)
    for(auto evt: elt.second)
        os << elt.first << " " << evt << endl;
}
