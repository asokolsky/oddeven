#include <stdexcept>
#include <algorithm> 
#include "database.h"
#include "condition_parser.h"
#include "test_runner.h"

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
    for(auto mit = _m.begin(); mit != _m.end(); ++mit)  // for all the dates in the map
    {
        // copy to thisDateEvents the events that meet the condition
        vector<pair<string,unsigned long>>thisDateEvents;
        for(auto sit = mit->second.begin(); sit != mit->second.end(); ++sit)
            if(predicate(mit->first, sit->first)) 
                thisDateEvents.push_back(*sit);

        // now sort thisDateEvents according to thisDateEvents[].second
        sort(thisDateEvents.begin(), thisDateEvents.end(), 
            [](const pair<string,unsigned long>& lhs, const pair<string,unsigned long>& rhs) {
                return lhs.second < rhs.second;
            });

        // now copy thisDateEvents into res
        for(const auto &evt: thisDateEvents) {
            stringstream os; 
            os << mit->first << " " << evt.first;
            res.push_back(os.str());
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
  {
    vector<pair<string,unsigned long>>v;
    // copy a set elt.second into a vector v
    for(const auto &evt: elt.second)
        v.push_back(evt);
    // now sort v by v[x].second
    sort(v.begin(), v.end(), 
        [](const pair<string,unsigned long>& lhs, const pair<string,unsigned long>& rhs) {
            return lhs.second < rhs.second;
        });
    // now just dump the properly ordered events
    for(const auto &evt: v)
        os << elt.first << " " << evt.first << endl;
  }
}

/**
 *  Tests
 */
int DoRemove (Database& db, const string& str) {
    istringstream is (str);
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date &date, const string &event) {
        return condition->Evaluate(date, event);
    };
    return db.RemoveIf(predicate);
}

string DoFind (Database& db, const string& str) {
    istringstream is (str);
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date &date, const string &event) {
        return condition->Evaluate(date, event);
    };
    const auto entries = db.FindIf(predicate);
    ostringstream os;
    for (const auto& entry : entries) {
        os << entry << endl;
    }
    os << entries.size();
    return os.str();
}

void TestDbAdd() {
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 7}, "xmas");
        ostringstream out;
        db.Print(out);
        AssertEqual("2017-01-01 new year\n2017-01-07 xmas\n", out.str(), "straight ordering");
    }
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 1}, "holiday");
        ostringstream out;
        db.Print(out);
        AssertEqual("2017-01-01 new year\n2017-01-01 holiday\n", out.str(), "several in one day");
    }
    {
        Database db;
        db.Add({2017, 1, 7}, "xmas");
        db.Add({2017, 1, 1}, "new year");
        ostringstream out;
        db.Print(out);
        AssertEqual("2017-01-01 new year\n2017-01-07 xmas\n", out.str(), "reverse ordering");
    }
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 1}, "xmas");
        db.Add({2017, 1, 1}, "new year");
        ostringstream out;
        db.Print(out);
        AssertEqual("2017-01-01 new year\n2017-01-01 xmas\n", out.str(), "uniq adding");
    }
}

void TestDbFind() {
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 7}, "xmas");
        AssertEqual("2017-01-01 new year\n1", DoFind(db, "date == 2017-01-01"), "simple find by date");
        AssertEqual("2017-01-01 new year\n2017-01-07 xmas\n2", DoFind(db, "date < 2017-01-31"), "multiple find by date");
        AssertEqual("2017-01-01 new year\n1", DoFind(db, R"(event != "xmas")"), "multiple find by holiday");
    }
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 1}, "new year2");
        db.Add({2017, 1, 7}, "xmas");
        AssertEqual("2017-01-01 new year\n2017-01-07 xmas\n2", DoFind(db, R"(date == 2017-01-07 OR event == "new year")"),
                "complex find or");
        AssertEqual("2017-01-01 new year\n1", DoFind(db, R"(date == 2017-01-01 AND event == "new year")"),
                    "complex find and");
        AssertEqual("0", DoFind(db, R"(date == 2017-01-09 AND event == "new year")"),
                    "complex find and, nothing");
    }
}

void TestDbLast(){
    Database db;
    db.Add({2017, 1, 1}, "new year");
    db.Add({2017, 1, 7}, "xmas");
    {
        try {
            db.Last({2016, 12, 31});
            Assert(false, "last, found no entries");
        } catch (...){
            Assert(true, "last, found no entries");

        }
    }
    {
        ostringstream os;
        os << db.Last({2017, 1, 2});
        AssertEqual("2017-01-01 new year", os.str(), "greater than date");
    }
    {
        ostringstream os;
        os << db.Last({2017, 1, 1});
        AssertEqual("2017-01-01 new year", os.str(), "eq to date");
    }
    {
        ostringstream os;
        os << db.Last({2017, 1, 10});
        AssertEqual("2017-01-07 xmas", os.str(), "greater than max date");
    }
}

void TestDbRemoveIf () {
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 7}, "xmas");
        AssertEqual(0, DoRemove(db, R"(event == "something")"), "Remove nothing");
        AssertEqual(1, DoRemove(db, R"(date == "2017-01-01")"), "Remove by date");
        ostringstream out;
        db.Print(out);
        AssertEqual("2017-01-07 xmas\n", out.str(), "Remove by date, left");
    }
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 7}, "xmas");
        AssertEqual(1, DoRemove(db, R"(event == "xmas")"), "Remove by event");
        ostringstream out;
        db.Print(out);
        AssertEqual("2017-01-01 new year\n", out.str(), "Remove by event, left");
    }
    {
        Database db;
        db.Add({2017, 1, 1}, "new year");
        db.Add({2017, 1, 7}, "xmas");
        db.Add({2017, 1, 7}, "new year");
        AssertEqual(2, DoRemove(db, R"(event == "new year")"), "Multiple remove by event");
        ostringstream out;
        db.Print(out);
        AssertEqual("2017-01-07 xmas\n", out.str(), "Multiple remove by event, left");
    }
}
