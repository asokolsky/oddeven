#include "node.h"

bool EmptyNode::Evaluate(const Date& date, const string& event) const
{
    return true;
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

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const
{
    bool bLHS = _lhs->Evaluate(date, event);
    switch(_op)
    {
        case Or:
            return (bLHS || _rhs->Evaluate(date, event));
        case And:
            return (bLHS && _rhs->Evaluate(date, event));
    }
    return false;
}
