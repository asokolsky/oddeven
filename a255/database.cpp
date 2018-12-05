#include <stdexcept>
#include "database.h"

void Database::Add(const Date& date, const string& event)
{
    if(event.empty())
        return;
    static unsigned long uGlobalCounter = 0;
    _m[date].insert(make_pair(event, uGlobalCounter++));
    // fix me! the above doe not work for updating the existing event!
}
/** returns the # of entries removed */
int Database::RemoveIf(std::function <bool(const Date& date, const string& event)> const &predicate)
{
    int iRemoved = 0;
    for(auto mit = _m.begin(); mit != _m.end(); ++mit)
    {
        for(auto sit = mit->second.begin(); sit != mit->second.end(); ++sit)
        {
            if(predicate(mit->first, sit->first)) 
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
            if(predicate(mit->first, sit->first)) 
            {
                stringstream os;
                os << mit->first << " " << sit->first;
                res.push_back(os.str());
            }
        }
    }
    return res; 
}

static string getLastEvent(const set<pair<string,unsigned long>, classcomp> &setOfPairs)
{
    pair<string,unsigned long>res;
    res.second = 0;
    for(auto p: setOfPairs)
        if(p.second >= res.second)
            res = p;
    return res.first;
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
    string event = getLastEvent(it->second);
    stringstream os;
    os << it->first << " " << event;
    return os.str();
}
void Database::Print(std::ostream& os) const
{
  for(const auto &elt: _m)
    for(const auto &evt: elt.second)
        os << elt.first << " " << evt.first << endl;
}
