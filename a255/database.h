#pragma once

#include <map>
#include "date.h"


class Database {
public:
    Database() {}

    void Add(date, event);
    void Print(cout);
    void RemoveIf(predicate);
    /** returns entries */
    void FindIf(predicate);
    /** throws exception */
    void Last(date);

    void AddEvent(const Date& date, const string& event);
    bool DeleteEvent(const Date& date, const string& event);
    int DeleteDate(const Date& date);
    void Find(const Date& date) const;
    void Print() const;
private:
    map<Date, set<string>> _m;
};
