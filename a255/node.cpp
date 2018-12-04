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
    return false;
}

EventComparisonNode::~EventComparisonNode()
{
}
bool EventComparisonNode::Evaluate(const Date& date, const string& event) const
{
    return false;
}
LogicalOperationNode::~LogicalOperationNode()
{
}
bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const
{
    return false;
}
