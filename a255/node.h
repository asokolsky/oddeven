#pragma once

using namespace std;

class Node {
public:
    Node() {}
};

class EmptyNode : public Node {
public:
    EmptyNode() {}

};

class DateComparisonNode : public Node {
public:
    DateComparisonNode() {}
}; 
class EventComparisonNode : public Node {
public:
    EventComparisonNode() {}
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode() {}
}; 

