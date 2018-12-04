#pragma once

using namespace std;

class Node {
public:
    Node() {}
    virtual bool Evaluate(const Date& date, const string& event) const;
};

class EmptyNode : public Node {
public:
    EmptyNode() {}

};

class DateComparisonNode : public Node {
    Date _date;
public:
    DateComparisonNode(const Date& date) : _date(date) {}
    bool Evaluate(const Date& date, const string& event) const;
}; 
class EventComparisonNode : public Node {
    string _event;
public:
    EventComparisonNode(const string& event) : _event(event) {}
    bool Evaluate(const Date& date, const string& event) const;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode() {}
    bool Evaluate(const Date& date, const string& event) const;
}; 

