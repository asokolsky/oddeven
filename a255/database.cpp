#include <stdexcept>
#include "database.h"

void Database::Add(const Date& date, const string& event)
{
    if(!event.empty())
        _m[date].insert(event);
}
/** returns the # of entries removed */
int Database::RemoveIf(std::function <bool(const Date& date, const string& event)> const &predicate)
{
    int iRemoved = 0;
    for(auto mit = _m.begin(); mit != _m.end(); ++mit)
    {
        for(auto sit = mit->second.begin(); sit != mit->second.end(); ++sit)
        {
            if(predicate(mit->first, *sit)) 
            {
                mit->second.erase(sit);
                iRemoved++;
            }
        }
        if(mit->second.empty())
            _m.erase(mit);
    }
    return iRemoved; 
}
/** returns entries */
vector<string> Database::FindIf(std::function <bool (const Date& date, const string& event)> const &predicate) const
{
    vector<string>res;
    for(auto mit = _m.begin(); mit != _m.end(); ++mit)
    {
        for(auto sit = mit->second.begin(); sit != mit->second.end(); ++sit)
        {
            if(predicate(mit->first, *sit)) 
            {
                stringstream os;
                os << mit->first << " " << *sit;
                res.push_back(os.str());
            }
        }
    }
    return res; 
}
/** 
 * throws invalid_argument exception if there is nothing before date 
 */
string Database::Last(const Date& date) const
{
    if(_m.empty())
        throw invalid_argument("No events yet");
    auto it = _m.lower_bound(date);
    if(it == _m.end())
        --it;
    if(date < it->first)
        throw invalid_argument("Nothing on or before that date");
    string res("found it");
    return res;
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
