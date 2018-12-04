#pragma once
#include <map>
#include <set>
#include <vector>
#include <string>
#include <functional>
#include "date.h"


class Database {
public:
    Database() {}
    void Add(const Date& date, const string& event);
    /** returns the # of entries removed */
    int RemoveIf(std::function <bool(const Date& date, const string& event)> const &predicate);
    /** returns entries */
    vector<string> FindIf(std::function <bool (const Date& date, const string& event)> const &predicate) const;
    /** throws exception */
    string Last(const Date& date) const;
    /** prints the entier content */
    void Print(std::ostream& os) const;
private:
    map<Date, set<string>> _m;
};
