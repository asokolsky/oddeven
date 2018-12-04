#include "node.h"

Node::Node()
{
}
Node::~Node()
{
}
bool Node::Evaluate(const Date& date, const string& event) const
{
    return false;
}

EmptyNode::EmptyNode()
{
}
EmptyNode::~EmptyNode()
{
}
DateComparisonNode::~DateComparisonNode()
{
}
bool DateComparisonNode::Evaluate(const Date& date, const string& event) const
{
    switch(_cmp)
    {
        case Less:
            return date < _date;
        case LessOrEqual:
            return date <= _date;
        case Greater:
            return date > _date;
        case GreaterOrEqual:
            return date >= _date;
        case Equal:
            return date == _date;
        case NotEqual:
            return date != _date;
    }
    return false;
}

EventComparisonNode::~EventComparisonNode()
{
}
bool EventComparisonNode::Evaluate(const Date& date, const string& event) const
{
    switch(_cmp)
    {
        case Less:
            return event < _event;
        case LessOrEqual:
            return event <= _event;
        case Greater:
            return event > _event;
        case GreaterOrEqual:
            return event >= _event;
        case Equal:
            return event == _event;
        case NotEqual:
            return event != _event;
    }
    return false;
}
LogicalOperationNode::~LogicalOperationNode()
{
}
bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const
{
    bool bRes = _lhs->Evaluate(date, event);
    switch(_op)
    {
        case Or:
            return bRes || _rhs->Evaluate(date, event);
        case And:
            return bRes && _rhs->Evaluate(date, event);
    }
    return false;
}
