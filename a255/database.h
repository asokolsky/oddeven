#pragma once
#include <map>
#include <functional>
#include "date.h"


class Database {
public:
    Database() {}
    void Add(const Date& date, const string& event);
    void RemoveIf(std::function <bool(const Date& date, const string& event)> const &predicate);
    /** returns entries */
    void FindIf(std::function <bool (const Date& date, const string& event)> const &predicate) const;
    /** throws exception */
    void Last(const Date& date);
    /** prints the entier content */
    void Print(ostream os) const;
private:
    map<Date, set<string>> _m;
};
