#pragma once
#include <map>
#include <set>
#include <vector>
#include <string>
#include <functional>
#include "date.h"

struct classcomp {
    /** compare event name, ignore its timestamp */
    bool operator() (const pair<string,unsigned long>& lhs, const pair<string,unsigned long>& rhs) const
    {
        return lhs.first < rhs.first;
    }
};


class Database {
public:
    Database() {}
    void Add(const Date& date, const string& event);
    /** returns the # of entries removed */
    int RemoveIf(std::function <bool(const Date& date, const string& event)> const &predicate);
    /** returns entries */
    vector<string> FindIf(std::function <bool (const Date& date, const string& event)> const &predicate) const;
    /** throws invalid_argument exception if there is nothing before date */
    string Last(const Date& date) const;
    /** prints the entier content */
    void Print(std::ostream& os) const;
private:
    map<Date, set<pair<string,unsigned long>, classcomp>> _m;
};
