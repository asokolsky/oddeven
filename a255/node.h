#pragma once
#include <memory>
#include "date.h"

using namespace std;

enum Comparison {
  Less, LessOrEqual, Greater, GreaterOrEqual, Equal, NotEqual
};
enum LogicalOperation {
  Or, And
};

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
    Comparison _cmp;
    Date _date;
public:
    DateComparisonNode(const Comparison cmp, const Date& date) : 
        _cmp(cmp), _date(date) {}
    bool Evaluate(const Date& date, const string& event) const;
}; 
class EventComparisonNode : public Node {
    Comparison _cmp;
    string _event;
public:
    EventComparisonNode(const Comparison cmp, const string& event) : 
      _cmp(cmp), _event(event) {}
    bool Evaluate(const Date& date, const string& event) const;
};

class LogicalOperationNode : public Node {
    LogicalOperation _op;
    shared_ptr<Node> _lhs;
    shared_ptr<Node> _rhs;
public:
    LogicalOperationNode(const LogicalOperation op, shared_ptr<Node> lhs, shared_ptr<Node> rhs) :
      _op(op), _lhs(lhs), _rhs(rhs)
    {
    }
    bool Evaluate(const Date& date, const string& event) const;
}; 

